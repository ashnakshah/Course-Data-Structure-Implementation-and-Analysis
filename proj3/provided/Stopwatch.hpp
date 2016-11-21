// Stopwatch.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// The Stopwatch class is used to measure CPU time consumption between
// the time that its start() and stop() member functions are called.

#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <ctime>



class Stopwatch
{
public:
    Stopwatch();

    void start();
    void stop();

    double lastDuration() const;


    class NotRunningException { };
    class RunningException { };

private:
    bool running;
    std::clock_t startTime;
    std::clock_t stopTime;
    double duration;
};



#endif // STOPWATCH_HPP

