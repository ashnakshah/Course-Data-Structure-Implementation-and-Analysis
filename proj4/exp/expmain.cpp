// expmain.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <fstream>
#include <iostream>
#include "RoadMap.hpp"

int main()
{
    std::ifstream ifs ("sample.txt");
//    InputReader ipr (ifs);
//    RoadMapReader rmr;
//    rmr.readRoadMap(ipr);

//    std::cout<<ipr.readLine()<<std::endl;
    ifs.close();

    return 0;
}

