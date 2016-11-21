// MazeSolutionException.hpp
//
// ICS 46 Spring 2016
// Project #1: Dark at the End of the Tunnel
//
// Exception thrown by a MazeSolution object when interacting with it in a
// way that's invalid, such as backing up when the solution is already empty
// or extending the solution outside of the boundaries of the maze.

#ifndef MAZESOLUTIONEXCEPTION_HPP
#define MAZESOLUTIONEXCEPTION_HPP

#include <string>



class MazeSolutionException
{
public:
    MazeSolutionException(const std::string& reason):
        reason{reason}
    {
    }

    std::string getReason() const
    {
        return reason;
    }

private:
    std::string reason;
};



#endif // MAZESOLUTIONEXCEPTION_HPP

