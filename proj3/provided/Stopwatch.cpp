// Stopwatch.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun

#include "Stopwatch.hpp"


Stopwatch::Stopwatch()
    : running{false}, duration{0.0}
{
}


void Stopwatch::start()
{
    if (!running)
    {
        startTime = std::clock();
        running = true;
    }
    else
    {
        throw Stopwatch::RunningException{};
    }
}


void Stopwatch::stop()
{
    std::clock_t currentTime = std::clock();

    if (running)
    {
        stopTime = currentTime;
        duration = (stopTime - startTime) / static_cast<double>(CLOCKS_PER_SEC);
        running = false;
    }
    else
    {
        throw Stopwatch::NotRunningException{};
    }
}


double Stopwatch::lastDuration() const
{
    return duration;
}

