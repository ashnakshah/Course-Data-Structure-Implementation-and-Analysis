#ifndef DEPTHFIRSTMAZEGENERATOR_HPP
#define DEPTHFIRSTMAZEGENERATOR_HPP 

#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include <utility>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>

class DFMazeGenerator:public MazeGenerator
{
    void genMR(std::pair<int,int> coord, Maze& maze, std::vector< std::pair<int,int> >& visited, int backtrack=0)
    {
     visited.push_back(coord);
     std::vector<int> dir_v=legalDirection(coord,visited,maze.getWidth(),maze.getHeight());       
//     std::cout<<"X:"<<coord.first<<" Y:"<<coord.second<<std::endl<<"DIR:"<<std::endl;
//     for(int i=0;i<dir_v.size();i++){std::cout<<dir_v[i]<<std::endl;}
     //std::cout<<"LAST VISITED: X="<<visited.back().first<<", Y="<<visited.back().second<<std::endl;
     while(dir_v.size()!=0)
     {
        int x=coord.first;
        int y=coord.second;
        int randomIndex=randomIndexGenerator(dir_v.size());
        //std::cout<<"RANDOM DIRECTION"<<dir_v[randomIndex]<<std::endl;
        switch(dir_v[randomIndex])
        {
            case 0:
                maze.removeWall(x,y,Direction::up);
                --y;
                break;
            case 1:
                maze.removeWall(x,y,Direction::down);
                ++y;
                break;
            case 2:
                maze.removeWall(x,y,Direction::left);
                --x;
                break;
            case 3:
                maze.removeWall(x,y,Direction::right);
                ++x;
                break;
            default:
                ;
        }
        genMR(std::make_pair(x,y),maze,visited);
        dir_v=legalDirection(coord,visited,maze.getWidth(),maze.getHeight());
     }
       
    }

int randomIndexGenerator(int random_size)
{
    std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(0,random_size-1);
    return dis(gen);

}

std::vector<int> legalDirection(std::pair<int,int> coord,std::vector< std::pair<int,int> > visited,int w, int h)
    {
        std::vector<int> direction;
        int x=coord.first;
        int y=coord.second;
        if (x-1>=0 && \
        find(visited.begin(),visited.end(),std::make_pair(x-1,y))==visited.end())
        direction.push_back(2);
        if (x+1<w && \
        find(visited.begin(),visited.end(),std::make_pair(x+1,y))==visited.end())
        direction.push_back(3);
        if (y-1>=0 && \
        find(visited.begin(),visited.end(),std::make_pair(x,y-1))==visited.end())
        direction.push_back(0);
        if (y+1<h && \
        find(visited.begin(),visited.end(),std::make_pair(x,y+1))==visited.end())
        direction.push_back(1);
        return direction;
}        
    
    public:
//        DepthFirstMazeGenerator();
        void generateMaze(Maze& maze);
};

/*
void genMR(std::pair<int,int> coord, Maze& maze, std::vector< std::pair<int,int> >& visited, int backtrack=0)
    {
//        std::cout<<"X:"<<coord.first<<"  Y:"<<coord.second<<std::endl;
        if(visited.size()==maze.getWidth()*maze.getHeight()) return ;
        else
        {   
            if (find(visited.begin(),visited.end(),coord)==visited.end()) visited.push_back(coord);
            std::vector<int> dir_v=legalDirection(coord,visited,maze.getWidth(),maze.getHeight());
            if (dir_v.size()==0)
            {
            ++backtrack;
            genMR(visited[visited.size()-backtrack],maze,visited,backtrack);
            }
            else
            {
                std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());
                std::uniform_int_distribution<int> dis(0,dir_v.size()-1);
                int ran=dis(gen);
                int x=coord.first;
                int y=coord.second;
                switch(dir_v[ran])
                {
                    case 0:   
                        maze.removeWall(coord.first,coord.second,Direction::up);
                        genMR(std::make_pair(x,y-1),maze,visited);
                        break;
                    case 1:
                        maze.removeWall(coord.first,coord.second,Direction::down);
                        genMR(std::make_pair(x,y+1),maze,visited);
                        break;
                    case 2:
                        maze.removeWall(coord.first,coord.second,Direction::left);
                        genMR(std::make_pair(x-1,y),maze,visited);
                        break;
                    case 3:
                        maze.removeWall(coord.first,coord.second,Direction::right);
                        genMR(std::make_pair(x+1,y),maze,visited);
                        break;
                    default:
                        ;
                }
                
            }
        }
    }

*/

#endif //DEPTHFIRSTMAZEGENERATOR_HPP
