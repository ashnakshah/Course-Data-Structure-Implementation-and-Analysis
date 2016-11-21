// MazeException.hpp
//
// ICS 46 Spring 2016
// Project #1: Dark at the End of the Tunnel
//
// Exception thrown when interacting with a Maze object in ways that are
// invalid (e.g., removing a non-existent wall or trying to create a maze
// with an invalid size like 0x0).

#ifndef MAZEEXCEPTION_HPP
#define MAZEEXCEPTION_HPP

#include <string>



class MazeException
{
public:
    MazeException(const std::string& reason):
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



#endif // MAZEEXCEPTION_HPP

