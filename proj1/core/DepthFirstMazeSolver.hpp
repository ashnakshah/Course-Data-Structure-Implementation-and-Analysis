#ifndef DEPTHFIRSTMAZESOLVER_HPP
#define DEPTHFIRSTMAZESOLVER_HPP 

#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include "Direction.hpp"

class DFMazeSolver: public MazeSolver
{
    static int count;
    std::vector<Direction> legalDirection(const Maze& maze,MazeSolution& mazeSolution)
    {
        std::vector<Direction> result;
        std::pair<int,int> currentCell=mazeSolution.getCurrentCell();
        int x=currentCell.first;
        int y=currentCell.second;
        std::vector< std::pair<int,int> > cells=mazeSolution.getCells();
        if(!maze.wallExists(x,y,Direction::up) &&\
        find(cells.begin(),cells.end(),std::make_pair(x,y-1))==cells.end())
        {result.push_back(Direction::up);}
        if(!maze.wallExists(x,y,Direction::down) &&\
        find(cells.begin(),cells.end(),std::make_pair(x,y+1))==cells.end())
        {result.push_back(Direction::down);}
        if(!maze.wallExists(x,y,Direction::left) &&\
        find(cells.begin(),cells.end(),std::make_pair(x-1,y))==cells.end())
        {result.push_back(Direction::left);}
        if(!maze.wallExists(x,y,Direction::right) &&\
        find(cells.begin(),cells.end(),std::make_pair(x+1,y))==cells.end())
        {result.push_back(Direction::right);}
//        std::cout<<"DIR"<<std::endl;
//        for(int i=0;i<result.size();i++){std::cout<<"["<<(int)result[i]<<"]"<<std::endl;}
        return result;
    }

    public:
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
};



#endif //DEPTHFIRSTMAZESOLVER_HPP


