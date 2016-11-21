#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "DepthFirstMazeSolver.hpp"
#include "Direction.hpp"
#include <vector>
#include <utility>
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver,DFMazeSolver,"Depth-First (Required)");

int DFMazeSolver::count=0;
void DFMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
//    std::cout<<"Current:"<<mazeSolution.getCurrentCell().first<<" "<<mazeSolution.getCurrentCell().second<<std::endl<<"LEVEL:"<<count++<<std::endl<<"DIR:"<<std::endl;
    std::vector<Direction> dir=legalDirection(maze,mazeSolution);
    for(int i=dir.size()-1;i>=0;i--)
    {
//        std::cout<<"["<<(int)dir[i]<<"]"<<std::endl;
        if (mazeSolution.isComplete()) break;
        mazeSolution.extend(dir[i]);
        solveMaze(maze,mazeSolution);
        if (mazeSolution.isComplete()) break;
        else ;
        mazeSolution.backUp();
    }
}

