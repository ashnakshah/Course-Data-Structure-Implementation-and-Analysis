#ifndef OTHELLOAITESTING_HPP
#define OTHELLOAITESTING_HPP

#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloBoard.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include "OthelloCell.hpp"
#include <memory>
#include <iostream>

namespace yitongw2
{

    class TestingAI: public OthelloAI
    {
        public:
            virtual std::pair<int,int> chooseMove(const OthelloGameState& state);
        private:
            OthelloCell turn=OthelloCell::empty;
            std::vector< std::pair<std::pair<int,int>,int> > validMoves(const OthelloGameState& s)
            {
                std::vector< std::pair<std::pair<int,int>,int> > valid_moves;
                for (int i=0;i<s.board().width();i++)
                {
                    for (int j=0;j<s.board().height();j++)
                    {
                        if (s.isValidMove(i,j))
                            valid_moves.push_back(std::make_pair(std::make_pair(i,j),0));
                        else ;
                    }
                }
                return valid_moves;
            }
            void setTurn(const OthelloGameState& s)
            {
                if (s.isWhiteTurn())
                    turn=OthelloCell::white;
                else if (s.isBlackTurn())
                    turn=OthelloCell::black;
                else ;
                    
            }
            bool isMyTurn(const OthelloGameState& s)
            {
                if (s.isBlackTurn()) return OthelloCell::black==turn;
                else return OthelloCell::white==turn;
            }
            int search(OthelloGameState& state,int depth)
            {
                if (depth==0) 
                {
                    return evaluate(state);
                }
                else
                {
                    std::vector< std::pair<std::pair<int,int>,int> > valid_moves=validMoves(state);
                    std::vector<int> result;
                    std::unique_ptr<OthelloGameState> gameStatePtr;
 //                   std::cout<<"DEPTH:"<<depth<<std::endl;
 //                   std::cout<<"SIZE:"<<valid_moves.size()<<std::endl;
                    for (int i=0;i<valid_moves.size();i++)
                    {
                        gameStatePtr=state.clone();
                        std::pair<int,int> coord=valid_moves[i].first;
   //                     std::cout<<"X="<<coord.first<<" Y="<<coord.second<<std::endl;
                        (*gameStatePtr).makeMove(coord.first,coord.second);
                        result.push_back(search(*gameStatePtr,depth-1));
                    }
                    if (!valid_moves.size())
                        return evaluate(state);
                    else
                    {
                        std::sort(result.begin(),result.end());
                        if (isMyTurn(state))
                            return result.back();
                        else 
                            return result[0];
                    }
                    /*if (isMyTurn(state))
                    {
                        
                        for (int i=0;i<valid_moves.size();i++)
                        {
                            gameStatePtr=state.clone();
                            std::pair<int,int> coord=valid_moves[i].first;
                            std::cout<<"X="<<coord.first<<" Y="<<coord.second<<std::endl;
                            (*gameStatePtr).makeMove(coord.first,coord.second);
                            result.push_back(search(*gameStatePtr,depth-1));
                        }
                        if (valid_moves.size())
                        {
                        std::sort(result.begin(),result.end());
                        return result.back();
                        }
                        else return evaluate(state);
                    }
                    else
                    {
                        for (int i=0;i<valid_moves.size();i++)
                        {
                            gameStatePtr=state.clone();
                            std::pair<int,int> coord=valid_moves[i].first;
                            (*gameStatePtr).makeMove(coord.first,coord.second);
                            result.push_back(search(*gameStatePtr,depth-1));
                        }
                        
                        if (valid_moves.size())
                        {
                        std::sort(result.begin(),result.end());
                        return result[0];
                        }
                        else return evaluate(state);
                    }*/
                }
            }
            int evaluate(OthelloGameState& s)
            {
                if (turn==OthelloCell::black)
                    return s.blackScore()-s.whiteScore();
                else
                    return s.whiteScore()-s.blackScore();
            }
            
    };

}

#endif //OTHELLOAITESTING_HPP
