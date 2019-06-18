#ifndef POSSIBLEMOVES_H_INCLUDED
#define POSSIBLEMOVES_H_INCLUDED

#include <vector>
#include <iostream> //debug
#include "board.h"  //debug

inline bool immobilized(std::vector<std::vector<char> > &b, int x, int y, bool white);
inline bool imitated(std::vector<std::vector<char> > &b, int x, int y, bool white);
inline void pCapture(std::vector<std::vector<char> > &tmp, int x, int y, bool white);
inline void bCaptureP(std::vector<std::vector<char> > &tmp, int x, int y, bool white);
inline std::vector<std::vector<char> > doMove(std::vector<std::vector<char> > &b, int x, int y, int xd, int yd);
inline void bCaptureKing(std::vector<std::vector<std::vector<char> > > &moves, std::vector<std::vector<char> > &b, int x, int y, bool white);
void possibleMovesPiece(std::vector<std::vector<std::vector<char> > > &moves, std::vector< std::vector<char> > &b, int x, int y, int xRoi, int yRoi, bool white);
inline std::pair<int, int> findKing(std::vector<std::vector<char> > &board, bool white);
std::vector<std::vector<std::vector<char> > > possibleMoves(std::vector< std::vector<char> > &board, bool white);
int getResult(std::vector<std::vector<char> > &board, bool white);

inline std::pair<int, int> findKing(std::vector<std::vector<char> > &board, bool white)
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

inline bool testCheck(std::vector<std::vector<char> > &board, bool white)
{
    std::vector<std::vector<std::vector<char> > > p(possibleMoves(board,!white));
    for(size_t i=0;i<p.size();i++)
    {
        if(findKing(p[i], white).first==-1)
        {
        	// std::cout<<"			King getting captured in this scenario :"<<std::endl<<"			"<<std::endl;
        	// printBoard(p[i]);
            return true;
        }
    }
    return false;
}

#endif // POSSIBLEMOVES_H_INCLUDED
