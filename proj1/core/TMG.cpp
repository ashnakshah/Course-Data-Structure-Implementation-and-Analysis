#include <ics46/factory/DynamicFactory.hpp>
#include "TMG.hpp"
#include "Direction.hpp"
#include <vector>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,TMG,"Testing")

void TMG::generateMaze(Maze& maze)
{
    maze.addAllWalls();
    std::vector< std::vector<bool> > vb (maze.getWidth(),std::vector<bool>(maze.getHeight()));
    gVb(maze,vb);
    recur(0,0,maze,vb);
}
