//main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "TripReader.hpp"
#include "RoadMap.hpp"
#include "Trip.hpp"
#include "RoadMapWriter.hpp"
#include <vector>
#include <utility>


void trans(double hrs,std::ostream& out)
{
    if (int(hrs)>0)
    {
        out<<(int)hrs<<" hrs ";
        hrs-=(int)hrs;
    }
    hrs*=60;
    if (int(hrs)>0)
    {
        out<<(int)hrs<<" mins ";
        hrs-=(int)hrs;
    }
    hrs*=60;
    if (int(hrs)>0)
    {
        out<<std::setprecision(3)<<hrs<<" secs ";
    }
}
int main()
{
    
    std::ifstream ifs("/home/ics46/projects/proj4/inputs/sample.txt");    
    InputReader ipr (ifs);
    RoadMapReader rmr;
    RoadMap rm=rmr.readRoadMap(ipr);
    TripReader tr;
    std::vector<Trip> trips (tr.readTrips(ipr));
    ifs.close();  
    RoadMap roadmap;
    roadmap=rm;
    if (!roadmap.isStronglyConnected())
    {
        std::cout<<"Disconnected Graph"<<std::endl;
        return 1;
    }
    std::vector<int> v;
    for (auto T:trips)
    {
        if (T.metric==TripMetric::Distance)
        {
            v=roadmap.findShortestPathsByDistance(T.startVertex,T.endVertex);
            std::cout<<"Shortest distance from "
            <<roadmap.vertexInfo(v.back())
            <<" to "
            <<roadmap.vertexInfo(v.front())<<std::endl
            <<"   Begin at "
            <<roadmap.vertexInfo(v.back())<<std::endl;
            double sum=0;
            for (int i=v.size()-2;i>=0;i--)
            {
                double s=roadmap.edgeInfo(v[i+1],v[i]).miles;
                std::cout<<"   Continue to "<<roadmap.vertexInfo(v[i])<<" ("<<s<<" miles)"<<std::endl;
                sum+=s;
            }
            std::cout<<"Total distance: "<<sum<<" miles"<<std::endl;
        }
        else
        {
            v=roadmap.findShortestPathsByDistance(T.startVertex,T.endVertex);
            std::cout<<"Shortest driving time from "
            <<roadmap.vertexInfo(v.back())
            <<" to "
            <<roadmap.vertexInfo(v.front())<<std::endl
            <<"   Begin at "
            <<roadmap.vertexInfo(v.back())<<std::endl;
            double sum=0;
            for (int i=v.size()-2;i>=0;i--)
            {
                double miles=roadmap.edgeInfo(v[i+1],v[i]).miles;
                double speed=roadmap.edgeInfo(v[i+1],v[i]).milesPerHour;
                double s=miles/speed;
                std::cout<<"   Continue to "<<roadmap.vertexInfo(v[i])<<" ("<<miles<<" miles @ "<<speed<<"mph) = ";
                trans(s,std::cout);
                std::cout<<std::endl;
                sum+=s;
            }
            std::cout<<"Total time: ";
            trans(sum,std::cout);
            std::cout<<std::endl;

        }
    }

    return 0;
}

