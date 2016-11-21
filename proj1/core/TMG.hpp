#ifndef TMG_HPP
#define TMG_HPP
#include "Direction.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>

class TMG: public MazeGenerator
{
    public:
        virtual void generateMaze(Maze& maze);
    private:
        std::vector<Direction> vD(int x, int y, Maze& m, std::vector< std::vector<bool> > vb)
        {
            std::vector<Direction> d;
            if(x-1>=0 && !vb[x-1][y])
            d.push_back(Direction::left);
            if(x+1<m.getWidth() && !vb[x+1][y])
            d.push_back(Direction::right);
            if(y-1>=0 && !vb[x][y-1])
            d.push_back(Direction::up);
            if(y+1<m.getHeight() && !vb[x][y+1])
            d.push_back(Direction::down);
            return d;
        }
        void gVb(Maze& m, std::vector< std::vector<bool> > vb)
        {
            for(int i=0;i<m.getWidth();i++)
            {
                for(int j=0;j<m.getHeight();j++)
                {
                    vb[i][j]=0;
                }
            }
        }

        void recur(int x, int y, Maze& m, std::vector< std::vector<bool> >& bv)
        {
            std::vector<Direction> d=vD(x,y,m,bv);
            bv[x][y]=1;
            while(d.size()!=0)
            {
                std::default_random_engine gen (std::chrono::system_clock::now().time_since_epoch().count());
                std::uniform_int_distribution<int> dis(0,d.size()-1);
                Direction dir=d[dis(gen)];
                m.removeWall(x,y,dir);
                if (dir==Direction::up)
                   recur(x,y-1,m,bv);
                else if (dir==Direction::down)
                   recur(x,y+1,m,bv);
                else if (dir==Direction::left)
                   recur(x-1,y,m,bv);
                else
                   recur(x+1,y,m,bv);
                d=vD(x,y,m,bv);
            }
    }
};

#endif //TMG_HPP
