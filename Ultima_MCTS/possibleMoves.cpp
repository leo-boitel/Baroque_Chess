#include "possibleMoves.h"

//#include "board.h"
//#include <iostream>
#include <cassert>



using namespace std;


inline bool immobilized(vector< vector<char> > &b, int x, int y, bool white)
{
    char c = white ? 'i' : 'I';
    bool xo = x!=0;
    bool x7 = x!=7;
    bool y0 = y!=0;
    bool y7 = y!=7;
    return ((xo && (b[x-1][y]==c || (y0 && b[x-1][y-1]==c) || (y7 && b[x-1][y+1]==c))) ||
       (x7 && (b[x+1][y]==c || (y0 && b[x+1][y-1]==c) || (y7 && b[x+1][y+1]==c))) ||
       (y0 && b[x][y-1]==c) ||(y7 && b[x][y+1]==c));
}

inline bool imitated(vector< vector<char> > &b, int x, int y, bool white)
{
    char c = white ? 'b' : 'B';
    bool xo = x!=0;
    bool x7 = x!=7;
    bool y0 = y!=0;
    bool y7 = y!=7;
    return ((xo && (b[x-1][y]==c || (y0 && b[x-1][y-1]==c) || (y7 && b[x-1][y+1]==c))) ||
       (x7 && (b[x+1][y]==c || (y0 && b[x+1][y-1]==c) || (y7 && b[x+1][y+1]==c))) ||
       (y0 && b[x][y-1]==c) ||(y7 && b[x][y+1]==c));
}

inline void pCapture(vector<vector<char> > &tmp, int x, int y, bool white)
{
    if(white)
    {
        if(x<6 && tmp[x+1][y]>95 && tmp[x+2][y]<95)
            tmp[x+1][y] = '_';
        if(y<6 && tmp[x][y+1]>95 && tmp[x][y+2]<95)
            tmp[x][y+1] = '_';
        if(x>1 && tmp[x-1][y]>95 && tmp[x-2][y]<95)
            tmp[x-1][y] = '_';
        if(y>1 && tmp[x][y-1]>95 && tmp[x][y-2]<95)
            tmp[x][y-1] = '_';
        return;
    }
    if(x<6 && tmp[x+1][y]<95 && tmp[x+2][y]>95)
        tmp[x+1][y] = '_';
    if(y<6 && tmp[x][y+1]<95 && tmp[x][y+2]>95)
        tmp[x][y+1] = '_';
    if(x>1 && tmp[x-1][y]<95 && tmp[x-2][y]>95)
        tmp[x-1][y] = '_';
    if(y>1 && tmp[x][y-1]<95 && tmp[x][y-2]>95)
        tmp[x][y-1] = '_';
}

inline void bCaptureP(vector<vector<char> > &tmp, int x, int y, bool white)
{
    if(white)
    {
    if(x<6 && tmp[x+1][y]=='p' && tmp[x+2][y]<95)
        tmp[x+1][y] = '_';
    if(y<6 && tmp[x][y+1]=='p' && tmp[x][y+2]<95)
        tmp[x][y+1] = '_';
    if(x>1 && tmp[x-1][y]=='p' && tmp[x-2][y]<95)
        tmp[x-1][y] = '_';
    if(y>1 && tmp[x][y-1]=='p' && tmp[x][y-2]<95)
        tmp[x][y-1] = '_';
    return;
    }
    if(x<6 && tmp[x+1][y]=='P' && tmp[x+2][y]>95)
        tmp[x+1][y] = '_';
    if(y<6 && tmp[x][y+1]=='P' && tmp[x][y+2]>95)
        tmp[x][y+1] = '_';
    if(x>1 && tmp[x-1][y]=='P' && tmp[x-2][y]>95)
        tmp[x-1][y] = '_';
    if(y>1 && tmp[x][y-1]=='P' && tmp[x][y-2]>95)
        tmp[x][y-1] = '_';
}

inline vector<vector<char> > doMove(vector<vector<char> > &b, int x, int y, int xd, int yd)
{
    vector<vector<char> > tmp(b);
    tmp[xd][yd] = tmp [x][y];
    tmp[x][y] = '_';
    return tmp;
}

inline void bCaptureKing(vector<vector<vector<char> > > &moves, vector<vector<char> > &b, int x, int y, bool white)
{
    char c = white ? 'k' : 'K';
    bool xo = x!=0;
    bool x7 = x!=7;
    bool y0 = y!=0;
    bool y7 = y!=7;
    if (xo)
    {
        if(b[x-1][y]==c)
        {
            moves.push_back(doMove(b,x,y,x-1,y));
            return;
        }
        if(y0 && b[x-1][y-1]==c)
        {
            moves.push_back(doMove(b,x,y,x-1,y-1));
            return;
        }
        if(y7 && b[x-1][y+1]==c)
        {
            moves.push_back(doMove(b,x,y,x-1,y+1));
            return;
        }
    }
    if(x7)
    {
        if(b[x+1][y]==c)
        {
            moves.push_back(doMove(b,x,y,x+1,y));
            return;
        }
        if(y0 && b[x+1][y-1]==c)
        {
            moves.push_back(doMove(b,x,y,x+1,y-1));
            return;
        }
        if(y7 && b[x+1][y+1]==c)
        {
            moves.push_back(doMove(b,x,y,x+1,y+1));
            return;
        }
    }
    if(y0 && b[x][y-1]==c)
    {
        moves.push_back(doMove(b,x,y,x,y-1));
        return;
    }
    if(y7 && b[x][y+1]==c)
    {
        moves.push_back(doMove(b,x,y,x,y+1));
        return;
    }
}

void possibleMovesPiece(vector<vector<vector<char> > > &moves, vector< vector<char> > &b, int x, int y, int xRoi, int yRoi, bool white)
{
    if(immobilized(b,x,y,white))
        return;
    bool jmp;
    if(white){
    switch(b[x][y])
    {
        case 'K':
            {
            if(x!=0)
            {
                if(b[x-1][y]>94)
                {
                    moves.push_back(doMove(b,x,y,x-1,y));
                }
                if(y!=0 && b[x-1][y-1]>94)
                {
                    moves.push_back(doMove(b,x,y,x-1,y-1));
                }
                 if(y!=7 && b[x-1][y+1]>94)
                {
                    moves.push_back(doMove(b,x,y,x-1,y+1));
                }
            }
            if(x!=7)
            {
                if(b[x+1][y]>94)
                {
                    moves.push_back(doMove(b,x,y,x+1,y));
                }
                if(y!=0 && b[x+1][y-1]>94)
                {
                    moves.push_back(doMove(b,x,y,x+1,y-1));
                }
                 if(y!=7 && b[x+1][y+1]>94)
                {
                    moves.push_back(doMove(b,x,y,x+1,y+1));
                }
            }
            if(y!=0 && b[x][y-1]>94)
            {
                moves.push_back(doMove(b,x,y,x,y-1));
            }
            if(y!=7 && b[x][y+1]>94)
            {
                moves.push_back(doMove(b,x,y,x,y+1));
            }
            return;
            }
        case 'P':
            {
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                pCapture(tmp, i, y, white);
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                pCapture(tmp, i, y, white);
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                pCapture(tmp, x, i, white);
                moves.push_back(tmp);
            }
            return;
            }
        case 'W':
            {
            //straight moves
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(x>0 && tmp[x-1][y]>95)
                    tmp[x-1][y] = '_';
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(x<7 && tmp[x+1][y]>95)
                    tmp[x+1][y] = '_';
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(y>0 && tmp[x][y-1]>95)
                    tmp[x][y-1] = '_';
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(y<7 && tmp[x][y+1]>95)
                    tmp[x][y+1] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                if(x>0 && y>0 && tmp[x-1][y-1]>95)
                    tmp[x-1][y-1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                if(x<7 && y<7 && tmp[x+1][y+1]>95)
                    tmp[x+1][y+1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));
                if(x>0 && y<7 && tmp[x-1][y+1]>95)
                    tmp[x-1][y+1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                if(x<7 && y>0 && tmp[x+1][y-1]>95)
                    tmp[x+1][y-1] = '_';
                moves.push_back(tmp);
            }
            return;
            }
        case 'C':
            {
            //straight moves
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(tmp[xRoi][y]>95)
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]>95)
                    tmp[i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(tmp[xRoi][y]>95)
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]>95)
                    tmp[i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(tmp[xRoi][i]>95)
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]>95)
                    tmp[x][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(tmp[xRoi][i]>95)
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]>95)
                    tmp[x][yRoi] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                if(tmp[xRoi][y+i]>95)
                    tmp[xRoi][y+i] = '_';
                if(tmp[x+i][yRoi]>95)
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                if(tmp[xRoi][y-i]>95)
                    tmp[xRoi][y-i] = '_';
                if(tmp[x-i][yRoi]>95)
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));
                   if(tmp[xRoi][y-i]>95)
                    tmp[xRoi][y-i] = '_';
                if(tmp[x+i][yRoi]>95)
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                if(tmp[xRoi][y+i]>95)
                    tmp[xRoi][y+i] = '_';
                if(tmp[x-i][yRoi]>95)
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            return;
            }
        case 'L':
            {
            //Prendre les deplacements du Withdrawer, enlever la capture, changer le if b[x][y]!='_' pour sauter
            //les pieces unes par unes
            //straight moves
            jmp = false;
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                {
                    if(b[i][y]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                for(int j=x+1;j<i;j++)
                    tmp[j][y] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                {
                    if(b[i][y]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                for(int j=x-1;j>i;j--)
                    tmp[j][y] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                {
                    if(b[x][i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                for(int j=y+1;j<i;j++)
                    tmp[x][j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                {
                    if(b[x][i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                for(int j=y-1;j>i;j--)
                    tmp[x][j] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7)
                    break;
                if(b[x+i][y+i] != '_')
                {
                    if(b[x+i][y+i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                for(int j=1;j<i;j++)
                    tmp[x+j][y+j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0)
                    break;
                if(b[x-i][y-i] != '_')
                {
                    if(b[x-i][y-i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                for(int j=1;j<i;j++)
                    tmp[x-j][y-j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0)
                    break;
                if(b[x+i][y-i] != '_')
                {
                    if(b[x+i][y-i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));
                for(int j=1;j<i;j++)
                    tmp[x+j][y-j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7)
                    break;
                if(b[x-i][y+i] != '_')
                {
                    if(b[x-i][y+i]<95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                for(int j=1;j<i;j++)
                    tmp[x-j][y+j] = '_';
                moves.push_back(tmp);
            }
            return;
            }
        case 'I':
            {
            //Verifier presence Imitator, sinon move classique
             //straight moves
            if(imitated(b,x,y,white))
                return; //empty
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back(doMove(b,x,y,i,y));
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                moves.push_back(doMove(b,x,y,i,y));
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back(doMove(b,x,y,x,i));
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                moves.push_back(doMove(b,x,y,x,i));
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x+i,y+i));
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x-i,y-i));
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x+i,y-i));
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x-i,y+i));
            }
            return;
            }
        case 'B':
            {
            //Moves classiques, checker les autres
            //straight moves
            bCaptureKing(moves,b,x,y,white);
            jmp = false;
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                {
                    if(b[i][y]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[i][y] = 'B';
                for(int j=x;j<i;j++)
                    tmp[j][y] = '_';
                if(x>0 && tmp[x-1][y]=='w')
                    tmp[x-1][y] = '_';
                if(tmp[xRoi][y]=='c')
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]=='c')
                    tmp[i][yRoi] = '_';
                pCapture(tmp,i,y,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                {
                    if(b[i][y]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[i][y] = 'B';
                for(int j=x;j>i;j--)
                    tmp[j][y] = '_';
                if(x<7 && tmp[x+1][y]=='w')
                    tmp[x+1][y] = '_';
                if(tmp[xRoi][y]=='c')
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]=='c')
                    tmp[i][yRoi] = '_';
                pCapture(tmp,i,y,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                {
                    if(b[x][i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x][i] = 'B';
                for(int j=y;j<i;j++)
                    tmp[x][j] = '_';
                if(y>0 && tmp[x][y-1]=='w')
                    tmp[x][y-1] = '_';
                if(tmp[xRoi][i]=='c')
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]=='c')
                    tmp[x][yRoi] = '_';
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                {
                    if(b[x][i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x][i] = 'B';
                for(int j=y;j>i;j--)
                    tmp[x][j] = '_';
                if(y<7 && tmp[x][y+1]=='w')
                    tmp[x][y+1] = '_';
                if(tmp[xRoi][i]=='c')
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]=='c')
                    tmp[x][yRoi] = '_';
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            //diagonals
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7)
                    break;
                if(b[x+i][y+i] != '_')
                {
                    if(b[x+i][y+i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x+i][y+i] = 'B';
                for(int j=0;j<i;j++)
                    tmp[x+j][y+j] = '_';
                if(x>0 && y>0 && tmp[x-1][y-1]=='w')
                    tmp[x-1][y-1] = '_';
                if(tmp[xRoi][y+i]=='c')
                    tmp[xRoi][y+i] = '_';
                if(tmp[x+i][yRoi]=='c')
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0)
                    break;
                if(b[x-i][y-i] != '_')
                {
                    if(b[x-i][y-i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x-i][y-i] = 'B';
                tmp[x][y] = '_';
                for(int j=0;j<i;j++)
                    tmp[x-j][y-j] = '_';
                if(x<7 && y<7 && tmp[x+1][y+1]=='w')
                    tmp[x+1][y+1] = '_';
                if(tmp[xRoi][y-i]=='c')
                    tmp[xRoi][y-i] = '_';
                if(tmp[x-i][yRoi]=='c')
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0)
                    break;
                if(b[x+i][y-i] != '_')
                {
                    if(b[x+i][y-i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x+i][y-i] = 'B';
                for(int j=0;j<i;j++)
                    tmp[x+j][y-j] = '_';
                if(x>0 && y<7 && tmp[x-1][y+1]=='w')
                    tmp[x-1][y+1] = '_';
                if(tmp[xRoi][y-i]=='c')
                    tmp[xRoi][y-i] = '_';
                if(tmp[x+i][yRoi]=='c')
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7)
                    break;
                if(b[x-i][y+i] != '_')
                {
                    if(b[x-i][y+i]!='l' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x-i][y+i] = 'B';
                for(int j=0;j<i;j++)
                    tmp[x-j][y+j] = '_';
                if(x<7 && y>0 && tmp[x+1][y-1]=='w')
                    tmp[x+1][y-1] = '_';
                if(tmp[xRoi][y+i]=='c')
                    tmp[xRoi][y+i] = '_';
                if(tmp[x-i][yRoi]=='c')
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            return;
            }
    }
    return;
    }
    switch(b[x][y])
    {
        case 'k':
            {
            if(x!=0)
            {
                if(b[x-1][y]<96)
                {
                    moves.push_back(doMove(b,x,y,x-1,y));
                }
                if(y!=0 && b[x-1][y-1]<96)
                {
                    moves.push_back(doMove(b,x,y,x-1,y-1));
                }
                 if(y!=7 && b[x-1][y+1]<96)
                {
                    moves.push_back(doMove(b,x,y,x-1,y+1));
                }
            }
            if(x!=7)
            {
                if(b[x+1][y]<96)
                {
                    moves.push_back(doMove(b,x,y,x+1,y));
                }
                if(y!=0 && b[x+1][y-1]<96)
                {
                    moves.push_back(doMove(b,x,y,x+1,y-1));
                }
                 if(y!=7 && b[x+1][y+1]<96)
                {
                    moves.push_back(doMove(b,x,y,x+1,y+1));
                }
            }
            if(y!=0 && b[x][y-1]<96)
            {
                moves.push_back(doMove(b,x,y,x,y-1));
            }
            if(y!=7 && b[x][y+1]<96)
            {
                moves.push_back(doMove(b,x,y,x,y+1));
            }
            return;
            }
        case 'p':
            {
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                pCapture(tmp, i, y, white);
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                pCapture(tmp, i, y, white);
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                pCapture(tmp, x, i, white);
                moves.push_back(tmp);
            }
            return;
            }

        case 'w':
         {
            //straight moves
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(x>0 && tmp[x-1][y]<95)
                    tmp[x-1][y] = '_';
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(x<7 && tmp[x+1][y]<95)
                    tmp[x+1][y] = '_';
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(y>0 && tmp[x][y-1]<95)
                    tmp[x][y-1] = '_';
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(y<7 && tmp[x][y+1]<95)
                    tmp[x][y+1] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                if(x>0 && y>0 && tmp[x-1][y-1]<95)
                    tmp[x-1][y-1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                if(x<7 && y<7 && tmp[x+1][y+1]<95)
                    tmp[x+1][y+1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));
                if(x>0 && y<7 && tmp[x-1][y+1]<95)
                    tmp[x-1][y+1] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                if(x<7 && y>0 && tmp[x+1][y-1]<95)
                    tmp[x+1][y-1] = '_';
                moves.push_back(tmp);
            }
            return;
            }

        case 'c':
            {
            //straight moves
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(tmp[xRoi][y]<95)
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]<95)
                    tmp[i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                if(tmp[xRoi][y]<95)
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]<95)
                    tmp[i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(tmp[xRoi][i]<95)
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]<95)
                    tmp[x][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                if(tmp[xRoi][i]<95)
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]<95)
                    tmp[x][yRoi] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                if(tmp[xRoi][y+i]<95)
                    tmp[xRoi][y+i] = '_';
                if(tmp[x+i][yRoi]<95)
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                if(tmp[xRoi][y-i]<95)
                    tmp[xRoi][y-i] = '_';
                if(tmp[x-i][yRoi]<95)
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));

                   if(tmp[xRoi][y-i]<95)
                    tmp[xRoi][y-i] = '_';
                if(tmp[x+i][yRoi]<95)
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                if(tmp[xRoi][y+i]<95)
                    tmp[xRoi][y+i] = '_';
                if(tmp[x-i][yRoi]<95)
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            return;
            }

        case 'l':
            {
            //Prendre les deplacements du Withdrawer, enlever la capture, changer le if b[x][y]!='_' pour sauter
            //les pieces unes par unes
            //straight moves
            jmp = false;
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                {
                    if(b[i][y]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                for(int j=x+1;j<i;j++)
                    tmp[j][y] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                {
                    if(b[i][y]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,i,y));
                for(int j=x-1;j>i;j--)
                    tmp[j][y] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                {
                    if(b[x][i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                for(int j=y+1;j<i;j++)
                    tmp[x][j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                {
                    if(b[x][i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x,i));
                for(int j=y-1;j>i;j--)
                    tmp[x][j] = '_';
                moves.push_back(tmp);
            }
            //diagonals
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7)
                    break;
                if(b[x+i][y+i] != '_')
                {
                    if(b[x+i][y+i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y+i));
                for(int j=1;j<i;j++)
                    tmp[x+j][y+j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0)
                    break;
                if(b[x-i][y-i] != '_')
                {
                    if(b[x-i][y-i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y-i));
                for(int j=1;j<i;j++)
                    tmp[x-j][y-j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0)
                    break;
                if(b[x+i][y-i] != '_')
                {
                    if(b[x+i][y-i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x+i,y-i));
                for(int j=1;j<i;j++)
                    tmp[x+j][y-j] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7)
                    break;
                if(b[x-i][y+i] != '_')
                {
                    if(b[x-i][y+i]>95 || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(doMove(b,x,y,x-i,y+i));
                for(int j=1;j<i;j++)
                    tmp[x-j][y+j] = '_';
                moves.push_back(tmp);
            }
            return;
            }
        case 'i':
            {
            //Verifier presence Imitator, sinon move classique
             //straight moves
            if(imitated(b,x,y,white))
                return; //empty
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back(doMove(b,x,y,i,y));
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                moves.push_back(doMove(b,x,y,i,y));
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back(doMove(b,x,y,x,i));
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                moves.push_back(doMove(b,x,y,x,i));
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x+i,y+i));
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x-i,y-i));
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x+i,y-i));
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                moves.push_back(doMove(b,x,y,x-i,y+i));
            }
            return;
            }
          case 'b':
            {
            //Moves classiques, checker les autres
            //straight moves
            bCaptureKing(moves, b,x,y,white);
            jmp = false;
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                {
                    if(b[i][y]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[i][y] = 'b';
                for(int j=x;j<i;j++)
                    tmp[j][y] = '_';
                if(x>0 && tmp[x-1][y]=='W')
                    tmp[x-1][y] = '_';
                if(tmp[xRoi][y]=='C')
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]=='C')
                    tmp[i][yRoi] = '_';
                pCapture(tmp,i,y,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                {
                    if(b[i][y]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[i][y] = 'b';
                for(int j=x;j>i;j--)
                    tmp[j][y] = '_';
                if(x<7 && tmp[x+1][y]=='W')
                    tmp[x+1][y] = '_';
                if(tmp[xRoi][y]=='C')
                    tmp[xRoi][y] = '_';
                if(tmp[i][yRoi]=='C')
                    tmp[i][yRoi] = '_';
                pCapture(tmp,i,y,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                {
                    if(b[x][i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x][i] = 'b';
                for(int j=y;j<i;j++)
                    tmp[x][j] = '_';
                if(y>0 && tmp[x][y-1]=='W')
                    tmp[x][y-1] = '_';
                if(tmp[xRoi][i]=='C')
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]=='C')
                    tmp[x][yRoi] = '_';
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                {
                    if(b[x][i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x][i] = 'b';
                for(int j=y;j>i;j--)
                    tmp[x][j] = '_';
                if(y<7 && tmp[x][y+1]=='W')
                    tmp[x][y+1] = '_';
                if(tmp[xRoi][i]=='C')
                    tmp[xRoi][i] = '_';
                if(tmp[x][yRoi]=='C')
                    tmp[x][yRoi] = '_';
                pCapture(tmp,x,i,white);
                moves.push_back(tmp);
            }
            //diagonals
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7)
                    break;
                if(b[x+i][y+i] != '_')
                {
                    if(b[x+i][y+i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x+i][y+i] = 'b';
                for(int j=0;j<i;j++)
                    tmp[x+j][y+j] = '_';
                if(x>0 && y>0 && tmp[x-1][y-1]=='W')
                    tmp[x-1][y-1] = '_';
                if(tmp[xRoi][y+i]=='C')
                    tmp[xRoi][y+i] = '_';
                if(tmp[x+i][yRoi]=='C')
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0)
                    break;
                if(b[x-i][y-i] != '_')
                {
                    if(b[x-i][y-i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x-i][y-i] = 'b';
                tmp[x][y] = '_';
                for(int j=0;j<i;j++)
                    tmp[x-j][y-j] = '_';
                if(x<7 && y<7 && tmp[x+1][y+1]=='W')
                    tmp[x+1][y+1] = '_';
                if(tmp[xRoi][y-i]=='C')
                    tmp[xRoi][y-i] = '_';
                if(tmp[x-i][yRoi]=='C')
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0)
                    break;
                if(b[x+i][y-i] != '_')
                {
                    if(b[x+i][y-i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x+i][y-i] = 'b';
                for(int j=0;j<i;j++)
                    tmp[x+j][y-j] = '_';
                if(x>0 && y<7 && tmp[x-1][y+1]=='W')
                    tmp[x-1][y+1] = '_';
                if(tmp[xRoi][y-i]=='C')
                    tmp[xRoi][y-i] = '_';
                if(tmp[x+i][yRoi]=='C')
                    tmp[x+i][yRoi] = '_';
                moves.push_back(tmp);
            }
            jmp = false;
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7)
                    break;
                if(b[x-i][y+i] != '_')
                {
                    if(b[x-i][y+i]!='L' || jmp)
                        break;
                    jmp = true;
                    continue;
                }
                if(jmp)
                    jmp = false;
                vector<vector<char> > tmp(b);
                tmp[x-i][y+i] = 'b';
                for(int j=0;j<i;j++)
                    tmp[x-j][y+j] = '_';
                if(x<7 && y>0 && tmp[x+1][y-1]=='W')
                    tmp[x+1][y-1] = '_';
                if(tmp[xRoi][y+i]=='C')
                    tmp[xRoi][y+i] = '_';
                if(tmp[x-i][yRoi]=='C')
                    tmp[x-i][yRoi] = '_';
                moves.push_back(tmp);
            }
            return;
            }
    //We return before here
    }
    return;

}



vector<vector< vector<char> > > possibleMoves(vector< vector<char> > &board, bool white)
{
    vector<vector< vector<char> > > moves(0);
    pair<int,int> roi = findKing(board,white);
    assert(roi.first!=-1);
    // reserve space more efficient ?
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            possibleMovesPiece(moves,board,i,j,roi.first,roi.second,white);
        }
    }
    return moves;
}




int getResult(vector<vector<char> > &board, bool white)
{
    pair<int,int> roi = findKing(board,white);
    if(roi.first==-1)
        return -1; //No king
    bool draw = true;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j] != '_' && board[i][j] != 'K' && board[i][j] != 'k')
            {
                draw = false;
                break;
            }
        }
    }
    if(draw)
        return 3;
    vector<vector<vector<char> > > p(possibleMoves(board,white));
    bool pat = true, echec = testCheck(board,white);
    for(size_t i=0;i<p.size();i++)
    {
        if(!testCheck(p[i],white))
        {
            pat=false;
            break;
        }
    }
    if(echec)
    {
        if(pat)
            return 1; //mat
        return 2;
    }
    if(pat)
        return 3;
    return 0; //normal
}

