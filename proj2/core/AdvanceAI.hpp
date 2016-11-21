#ifndef ADVANCEAI_HPP
#define ADVANCEAI_HPP

#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include "OthelloCell.hpp"
#include <memory>

namespace yitongw2
{

    class AdvanceAI: public OthelloAI
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
                    for (int i=0;i<valid_moves.size();i++)
                    {
                        gameStatePtr=state.clone();
                        std::pair<int,int> coord=valid_moves[i].first;
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
                }
            }
            int evaluate(OthelloGameState& s)
            {
                if (turn==OthelloCell::black)
                    return (s.blackScore()+\
                    cornerScore(s,turn))-\
                    (s.whiteScore()+\
                    cornerScore(s,OthelloCell::white));
                else
                    return (s.whiteScore()+\
                    cornerScore(s,turn))-\
                    (s.blackScore()+\
                    cornerScore(s,OthelloCell::black));
            }
            int cornerScore(const OthelloGameState& s,OthelloCell c)
            {
                int w=s.board().width();
                int h=s.board().height();
                return corner(0,0,s,c)\
                +corner(0,h-1,s,c)\
                +corner(w-1,0,s,c)\
                +corner(w-1,h-1,s,c);
            }
            int corner(int x, int y, const OthelloGameState& s, OthelloCell c)
            {
                int cof;
                if (s.board().cellAt(x,y)==c) cof=3;
                else cof=-3;
                return (s.board().cellAt(x,y)==c)*5\
                +cof\
                *(\
                (s.board().isValidCell(x,y-1) && s.board().cellAt(x,y-1)==c)\
                +(s.board().isValidCell(x,y+1) && s.board().cellAt(x,y+1)==c)\
                +(s.board().isValidCell(x-1,y) && s.board().cellAt(x-1,y)==c)\
                +(s.board().isValidCell(x+1,y) && s.board().cellAt(x+1,y)==c)\
                );
            }
            int edgeScore(OthelloGameState& s,OthelloCell c)
            {
                return 0;
            }
    };

}

#endif //ADVANCEAI_HPP
