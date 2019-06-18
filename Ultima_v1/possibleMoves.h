#ifndef POSSIBLEMOVES_H_INCLUDED
#define POSSIBLEMOVES_H_INCLUDED

#include <vector>
#include <iostream> //debug
#include "board.h"  //debug
//#include "types.h" //included in board

bool immobilized(const std::vector<std::vector<char> > &b, int x, int y, bool white);
bool imitated(const std::vector<std::vector<char> > &b, int x, int y, bool white);
void pCapture(std::vector<std::vector<char> > &tmp, int x, int y, bool white);
void bCaptureP(std::vector<std::vector<char> > &tmp, int x, int y, bool white);
std::vector<std::vector<char> > doMove(const std::vector<std::vector<char> > &b, tmove m); //inline it here ?
std::vector<std::vector<char> > doMove(const std::vector<std::vector<char> > &b, int x, int y, int xd, int yd);
void bCaptureKing(std::vector<std::vector<std::vector<char> > > &moves, const std::vector<std::vector<char> > &b, int x, int y, bool white);
void possibleMovesPiece(std::vector<tmove> &moves, const std::vector< std::vector<char> > &b, int x, int y, int xRoi, int yRoi, bool white);
std::pair<int, int> findKing(const std::vector<std::vector<char> > &board, bool white);
std::vector<tmove> possibleMoves(const std::vector< std::vector<char> > &board, bool white);
std::vector<tmove> randomPossibleMoves(const std::vector< std::vector<char> > &board, bool white, std::vector<int> &range);
int getResult(const std::vector<std::vector<char> > &board, bool white);
int getResultFast(const std::vector<std::vector<char> > &board, bool white, bool legalMoves);
std::vector<tmove> possibleLegalMoves(const std::vector< std::vector<char> > &board, bool white);


inline std::pair<int, int> findKing(const std::vector<std::vector<char> > &board, bool white)
{
    char roi = white ? 'K' : 'k';
    int xR=0, yR = 0; //TODO : set to -1 to check for king presence, and manage it to find winning pos.
    for(;xR<8;xR++)
    {
        for(yR=0;yR<8;yR++)
        {
            if(board[xR][yR]==roi)
            {
                return std::make_pair(xR,yR);
            }
        }
    }
    // No king found !
    return std::make_pair(-1,-1);
}

inline bool testCheck(const std::vector<std::vector<char> > &board, bool white)
{
    std::vector<tmove> p(possibleMoves(board,!white));
    for(size_t i=0;i<p.size();i++)
    {
    	/*#ifndef NDEBUG
    	std::cout<<"Before doMove p["<<i<<"] out of "<<p.size()<<std::endl;
    	#endif*/
        if(findKing(doMove(board,p[i]), white).first==-1)
        {
        	// std::cout<<"			King getting captured in this scenario :"<<std::endl<<"			"<<std::endl;
        	// printBoard(p[i]);
            return true;
        }
    }
    return false;
}

#endif // POSSIBLEMOVES_H_INCLUDED
