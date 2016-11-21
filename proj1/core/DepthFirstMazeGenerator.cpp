#include <ics46/factory/DynamicFactory.hpp>
#include "DepthFirstMazeGenerator.hpp"
#include "Direction.hpp"
#include <vector>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,DFMazeGenerator,"Depth-First (Required)")

//a perfect maze is one in which any two cells are connected by a single unique path


void DFMazeGenerator::generateMaze(Maze& maze){
    maze.addAllWalls();
    std::vector< std::pair<int,int> > v;
    genMR(std::make_pair(0,0),maze,v);
}
