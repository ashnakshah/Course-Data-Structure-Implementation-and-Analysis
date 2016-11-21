#include "OthelloGameState.hpp"
#include "OthelloAITesting.hpp"
#include "OthelloBoard.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <utility>
#include <iostream>
#include <memory>
#include <algorithm>
//#include <time.h>
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,yitongw2::TestingAI,"TestingAI(Required)");

std::pair<int,int> yitongw2::TestingAI::chooseMove(const OthelloGameState& state)
{
    /*clock_t start,end;
    double cpu_time_used;
    start=clock();*/
    std::unique_ptr<OthelloGameState> stateCopy;
    std::vector< std::pair<std::pair<int,int>,int> > choices=validMoves(state);
    setTurn(state);
    for(int i=0;i<choices.size();i++)
    {
        stateCopy=state.clone();
        (*stateCopy).makeMove(choices[i].first.first,choices[i].first.second);
        choices[i].second=search(*stateCopy,3);
      //  std::cout<<"chooseMove::loop "<<i<<" result:"<<choices[i].second<<std::endl;
    }
    std::sort(choices.begin(),choices.end(),[](std::pair<std::pair<int,int>,int> i,std::pair<std::pair<int,int>,int> s){return i.second<s.second;});
    //std::cout<<"AI_CHOOSE_MOVE:("<<choices.back().first.first<<","<<choices.back().first.second<<")"<<std::endl;
    //end=clock();
    //cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
    //std::cout<<"CPU_TIME_USED: "<<cpu_time_used<<std::endl;
    return choices.back().first;
}
