#include "possibleMoves.h"

//#include "board.h"
//#include <iostream>
#include <cassert>
#include <numeric>

using namespace std;

bool immobilized(const vector< vector<char> > &b, int x, int y, bool white)
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

bool imitated(const vector< vector<char> > &b, int x, int y, bool white)
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

void pCapture(vector<vector<char> > &tmp, int x, int y, bool white)
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

void bCaptureP(vector<vector<char> > &tmp, int x, int y, bool white)
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

std::vector<std::vector<char> > doMove(const std::vector<std::vector<char> > &b, tmove m)
{
    return doMove(b,m[0],m[1],m[2],m[3]);
}

vector<vector<char> > doMove(const vector<vector<char> > &b, int x, int y, int xd, int yd)
{
    /*#ifndef NDEBUG
        cout<<"Trying move "<<b[x][y]<<" in "<<x<<y<<" to "<<xd<<yd<<endl;
    #endif*/
    vector<vector<char> > tmp(b);
    switch(tmp[x][y])
    {
        case 'K':
            tmp[x][y] = '_';
            tmp[xd][yd] = 'K';
            return tmp;
        case 'k':
            tmp[x][y] = '_';
            tmp[xd][yd] = 'k';
            return tmp;
        case 'W':
          {
            tmp[xd][yd] = 'W';
            tmp[x][y] = '_';
            int xp = (x>xd) ? 1 : -1;
            int yp = (y>yd) ? 1 : -1;
            if(x==xd)
                xp = 0;
            if(y==yd)
                yp = 0;
            xp += x;
            yp += y;
            if(xp>=0 && xp<8 && yp >= 0 && yp<8 && tmp[xp][yp]>95)
                tmp[xp][yp] = '_';
            return tmp;
          }
        case 'w':
         {
            tmp[xd][yd] = 'w';
            tmp[x][y] = '_';
            int xp = (x>xd) ? 1 : -1;
            int yp = (y>yd) ? 1 : -1;
            if(x==xd)
                xp = 0;
            if(y==yd)
                yp = 0;
            xp += x;
            yp += y;
            if(xp>=0 && xp<8 && yp >= 0 && yp<8 && tmp[xp][yp]<95)
                tmp[xp][yp] = '_';
            return tmp;
         }
        case 'P':
            tmp[xd][yd] = 'P';
            tmp[x][y] = '_';
            pCapture(tmp,xd,yd,true);
            return tmp;
        case 'p':
            tmp[xd][yd] = 'p';
            tmp[x][y] = '_';
            pCapture(tmp,xd,yd,false);
            return tmp;
        case 'L':
            {
            if(y==yd)
            {
                int eps = (x>xd) ? -1 : 1;
                for(;x!=xd;x+=eps)
                {
                    tmp[x][yd] = '_';
                }
                tmp[xd][yd] = 'L';
                return tmp;
            }
            if(x==xd)
            {
                int eps = (y>yd) ? -1 : 1;
                for(;y!=yd;y+=eps)
                {
                    tmp[xd][y] = '_';
                }
                tmp[xd][yd] = 'L';
                return tmp;
            }  
            int epsx = (x>xd) ? -1 : 1;
            int epsy = (y>yd) ? -1 : 1;
            for(;x!=xd;x+=epsx)
            {
                tmp[x][y] = '_';
                y+=epsy;
            }
            tmp[xd][yd] = 'L';
            return tmp;   
            }
        case 'l':
            {
            if(y==yd)
            {
                int eps = (x>xd) ? -1 : 1;
                for(;x!=xd;x+=eps)
                {
                    tmp[x][yd] = '_';
                }
                tmp[xd][yd] = 'l';
                return tmp;
            }
            if(x==xd)
            {
                int eps = (y>yd) ? -1 : 1;
                for(;y!=yd;y+=eps)
                {
                    tmp[xd][y] = '_';
                }
                tmp[xd][yd] = 'l';
                return tmp;
            }  
            int epsx = (x>xd) ? -1 : 1;
            int epsy = (y>yd) ? -1 : 1;
            for(;x!=xd;x+=epsx)
            {
                tmp[x][y] = '_';
                y+=epsy;
            }
            tmp[xd][yd] = 'l';
            return tmp;  
            }  

        // COORDINATOR OPTIMIZATION : GET XROI YROI AS ARG
        case 'C': 
            {
            pair<int,int> cRoi = findKing(tmp, true);
            if(tmp[cRoi.first][yd]>95)
                tmp[cRoi.first][yd] = '_';
            if(tmp[xd][cRoi.second]>95)
                tmp[xd][cRoi.second] = '_';
            tmp[x][y] = '_';
            tmp[xd][yd] = 'C';
            return tmp;
            }
        case 'c': 
            {
            pair<int,int> cRoi = findKing(tmp, false);
            if(tmp[cRoi.first][yd]<95)
                tmp[cRoi.first][yd] = '_';
            if(tmp[xd][cRoi.second]<95)
                tmp[xd][cRoi.second] = '_';
            tmp[x][y] = '_';
            tmp[xd][yd] = 'c';
            return tmp;
            }
        case 'B':
            {
            tmp[x][y] = '_';
            int xp = (x>xd) ? 1 : -1;
            int yp = (y>yd) ? 1 : -1;
            if(x==xd)
                xp = 0;
            if(y==yd)
                yp = 0;
            int xw = x + xp;
            int yw = y + yp;
            if(xw>=0 && xw<8 && yw >= 0 && yw<8 && tmp[xw][yw] == 'w')
                tmp[xw][yw] = '_';
            bCaptureP(tmp,xd,yd,true);
            pair<int,int> cRoi = findKing(tmp, true);
            if(tmp[cRoi.first][yd] == 'c')
                tmp[cRoi.first][yd] = '_';
            if(tmp[xd][cRoi.second] == 'c')
                tmp[xd][cRoi.second] = '_';
            tmp[xd][yd] = 'B';
            if(xp==0)
            {
                for(y-=yp;y!=yd;y-=yp)
                {
                    if(tmp[xd][y] == 'l')
                        tmp[xd][y] = ' ';
                }
                return tmp;
            }
            if(yp==0)
            {
                for(x-=xp;x!=xd;x-=xp)
                {
                    if(tmp[x][yd] == 'l')
                        tmp[x][yd] = ' ';
                }
                return tmp;
            }
            for(x-=xp;x!=xd;x-=xp)
            {
                y-=yp;
                if(tmp[x][y] == 'l')
                    tmp[x][y] = ' ';
            }
            return tmp;
            }
        case 'b':
            {
            tmp[x][y] = '_';
            int xp = (x>xd) ? 1 : -1;
            int yp = (y>yd) ? 1 : -1;
            if(x==xd)
                xp = 0;
            if(y==yd)
                yp = 0;
            int xw = x + xp;
            int yw = y + yp;
            if(xw>=0 && xw<8 && yw >= 0 && yw<8 && tmp[xw][yw] == 'W')
                tmp[xw][yw] = '_';
            bCaptureP(tmp,xd,yd,false);
            pair<int,int> cRoi = findKing(tmp, false);
            if(tmp[cRoi.first][yd] == 'C')
                tmp[cRoi.first][yd] = '_';
            if(tmp[xd][cRoi.second] == 'C')
                tmp[xd][cRoi.second] = '_';
            tmp[xd][yd] = 'b';
            if(xp==0)
            {
                for(y-=yp;y!=yd;y-=yp)
                {
                    if(tmp[xd][y] == 'L')
                        tmp[xd][y] = ' ';
                }
                return tmp;
            }
            if(yp==0)
            {
                for(x-=xp;x!=xd;x-=xp)
                {
                    if(tmp[x][yd] == 'L')
                        tmp[x][yd] = ' ';
                }
                return tmp;
            }
            for(x-=xp;x!=xd;x-=xp)
            {
                y-=yp;
                if(tmp[x][y] == 'L')
                    tmp[x][y] = ' ';
            }    
            return tmp;    
            }
        case 'i':
            tmp[x][y] = '_';
            tmp[xd][yd] = 'i';
            return tmp;
        case 'I':
            tmp[x][y] = '_';
            tmp[xd][yd] = 'I';
            return tmp;
    }
    return tmp;
}

void bCaptureKing(vector<tmove> &moves, const vector<vector<char> > &b, int x, int y, bool white)
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
            moves.push_back({x,y,x-1,y});
            return;
        }
        if(y0 && b[x-1][y-1]==c)
        {
            moves.push_back({x,y,x-1,y-1});
            return;
        }
        if(y7 && b[x-1][y+1]==c)
        {
            moves.push_back({x,y,x-1,y+1});
            return;
        } 
    }
    if(x7)
    {
        if(b[x+1][y]==c)
        {
            moves.push_back({x,y,x+1,y});
            return;
        }
        if(y0 && b[x+1][y-1]==c)
        {
            moves.push_back({x,y,x+1,y-1});
            return;
        }
        if(y7 && b[x+1][y+1]==c)
        {
            moves.push_back({x,y,x+1,y+1});
            return;
        }
    }
    if(y0 && b[x][y-1]==c)
    {
        moves.push_back({x,y,x,y-1});
        return;
    }
    if(y7 && b[x][y+1]==c)
    {
        moves.push_back({x,y,x,y+1});
        return;
    }
}

void possibleMovesPiece(vector<tmove> &moves, const vector< vector<char> > &b, int x, int y, int xRoi, int yRoi, bool white)
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
                    moves.push_back({x,y,x-1,y});
                }
                if(y!=0 && b[x-1][y-1]>94)
                {
                    moves.push_back({x,y,x-1,y-1});
                }
                 if(y!=7 && b[x-1][y+1]>94)
                {
                    moves.push_back({x,y,x-1,y+1});
                }
            }
            if(x!=7)
            {
                if(b[x+1][y]>94)
                {
                    moves.push_back({x,y,x+1,y});
                }
                if(y!=0 && b[x+1][y-1]>94)
                {
                    moves.push_back({x,y,x+1,y-1});
                }
                if(y!=7 && b[x+1][y+1]>94)
                {
                    moves.push_back({x,y,x+1,y+1});
                }
            }
            if(y!=0 && b[x][y-1]>94)
            {
                moves.push_back({x,y,x,y-1});
            }
            if(y!=7 && b[x][y+1]>94)
            {
                moves.push_back({x,y,x,y+1});
            }
            return;
            }
        case 'P':
            {
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=x-1;i>=0;i--)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            for(int i=y-1;i>=0;i--)
            {
                if(b[x][i]!='_')
                    break;
               moves.push_back({x,y,x,i});
            }
            return;
            }
        case 'W':
        case 'C':
        case 'I':
            {
            //Verifier presence Imitator, sinon tmove classique
             //straight moves
            if(imitated(b,x,y,white) && b[x][y]=='I')
                return; //empty
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                moves.push_back({x,y,x+i,y+i});
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                moves.push_back({x,y,x-i,y-i});
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                moves.push_back({x,y,x+i,y-i});
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                moves.push_back({x,y,x-i,y+i});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x+i,y+i});
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
                moves.push_back({x,y,x-i,y-i});
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
                moves.push_back({x,y,x+i,y-i});
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
                moves.push_back({x,y,x-i,y+i});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x+i,y+i});
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
                moves.push_back({x,y,x-i,y-i});
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
                moves.push_back({x,y,x+i,y-i});
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
                moves.push_back({x,y,x-i,y+i});
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
                    moves.push_back({x,y,x-1,y});
                }
                if(y!=0 && b[x-1][y-1]<96)
                {
                    moves.push_back({x,y,x-1,y-1});
                }
                 if(y!=7 && b[x-1][y+1]<96)
                {
                    moves.push_back({x,y,x-1,y+1});
                }
            }
            if(x!=7)
            {
                if(b[x+1][y]<96)
                {
                    moves.push_back({x,y,x+1,y});
                }
                if(y!=0 && b[x+1][y-1]<96)
                {
                    moves.push_back({x,y,x+1,y-1});
                }
                 if(y!=7 && b[x+1][y+1]<96)
                {
                    moves.push_back({x,y,x+1,y+1});
                }
            }
            if(y!=0 && b[x][y-1]<96)
            {
                moves.push_back({x,y,x,y-1});
            }
            if(y!=7 && b[x][y+1]<96)
            {
                moves.push_back({x,y,x,y+1});
            }
            return;
            }
        case 'p':
            {
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=x-1;i>=0;i--)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            for(int i=y-1;i>=0;i--)
            {
                if(b[x][i]!='_')
                    break;
               moves.push_back({x,y,x,i});
            }
            return;
            }
        case 'w':
        case 'c':
        case 'i':
            {
            //Verifier presence Imitator, sinon tmove classique
             //straight moves
            if(imitated(b,x,y,white) && b[x][y] == 'i')
                return; //empty
            for(int i=x+1;i<8;i++)
            {
                if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=x-1;i>=0;i--)
            {
               if(b[i][y]!='_')
                    break;
                moves.push_back({x,y,i,y});
            }
            for(int i=y+1;i<8;i++)
            {
                if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            for(int i=y-1;i>=0;i--)
            {
               if(b[x][i]!='_')
                    break;
                moves.push_back({x,y,x,i});
            }
            //diagonals
            for(int i=1;;i++)
            {
                if(x+i>7 || y+i>7 || b[x+i][y+i] != '_')
                    break;
                moves.push_back({x,y,x+i,y+i});
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y-i<0 || b[x-i][y-i] != '_')
                    break;
                moves.push_back({x,y,x-i,y-i});
            }
            for(int i=1;;i++)
            {
                if(x+i>7 || y-i<0 || b[x+i][y-i] != '_')
                    break;
                moves.push_back({x,y,x+i,y-i});
            }
            for(int i=1;;i++)
            {
                if(x-i<0 || y+i>7 || b[x-i][y+i] != '_')
                    break;
                moves.push_back({x,y,x-i,y+i});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x+i,y+i});
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
                moves.push_back({x,y,x-i,y-i});
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
                moves.push_back({x,y,x+i,y-i});
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
                moves.push_back({x,y,x-i,y+i});
            }
            return;
            }
        case 'b':
            {
            //Moves classiques, checker les autres
            //straight moves
            bCaptureKing(moves,b,x,y,white);
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,i,y});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x,i});
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
                moves.push_back({x,y,x+i,y+i});
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
                moves.push_back({x,y,x-i,y-i});
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
                moves.push_back({x,y,x+i,y-i});
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
                moves.push_back({x,y,x-i,y+i});
            }
            return;
            }
    //We return before here
    }
    return;

}

vector<tmove> possibleMoves(const vector< vector<char> > &board, bool white)
{
    vector<tmove> moves(0);
    pair<int,int> roi = findKing(board,white);
    // reserve space more efficient ?
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            possibleMovesPiece(moves,board,i,j,roi.first,roi.second,white);
           /* #ifndef NDEBUG
            for(int k=0;k<moves.size();k++)
            {
                if(moves[k][1]>=8 || moves[k][1]<0)
                    cout<<i<<j<<" : "<<board[i][j]<<endl;
            }
            #endif */
        }
    }
    return moves;
}

vector<tmove> randomPossibleMoves(const vector< vector<char> > &board, bool white, vector<int> &range)
{
    vector<tmove> moves(0);
    pair<int,int> roi = findKing(board,white);
    // reserve space more efficient ?
    int square,i,j;
    if(white)
    {
        while(moves.size()==0 && range.size()!=0)
        {
            square = rand()%range.size();
            i = range[square] % 8;
            j = (range[square] - i)/8;
            if(board[i][j]>=95)
            {
                range.erase(range.begin()+square);
            }
            else
            {
                possibleMovesPiece(moves,board,i,j,roi.first,roi.second,white);
                range.erase(range.begin()+square);  
            }
        }
    }
    else
    {
        while(moves.size()==0 && range.size()!=0)
        {
            square = rand()%range.size();
            i = range[square] % 8;
            j = (range[square] - i)/8;
            if(board[i][j]<=95)
            {
                range.erase(range.begin()+square);
            }
            else
            {
                possibleMovesPiece(moves,board,i,j,roi.first,roi.second,white);
                range.erase(range.begin()+square);  
            }
        }
    }
    return moves;
}

vector<tmove> possibleLegalMoves(const vector< vector<char> > &board, bool white)
{
    vector<tmove> moves(possibleMoves(board,white));
    vector<tmove> legalMoves(0);
    for(int i=0;i<moves.size();i++)
    {
        vector<vector<char> > nextBoard(doMove(board,moves[i]));
        vector<tmove> next(possibleMoves(nextBoard,!white));
        bool legal = true;
        for(int j=0;j<next.size();j++)
        {
            #ifndef NDEBUG
            /*if(findKing(nextBoard,!white).first==-1)
            {
                printBoard(board);
                cout<<endl;
                printBoard(nextBoard);
                cout<<"--------------------------------------------------------------------"<<endl;
            }*/
            #endif
            pair<int,int> roi = findKing(doMove(nextBoard,next[j]),white);
            if(roi.first == -1)
            {
                legal = false;
                break;
            }
        }
        if(legal)
            legalMoves.push_back(moves[i]);
    }
    return legalMoves;
}

int getResult(const vector<vector<char> > &board, bool white)
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
    vector<tmove> p(possibleMoves(board,white));
    bool pat = true, echec = testCheck(board,white);
    for(size_t i=0;i<p.size();i++)
    {
        if(!testCheck(doMove(board,p[i]),white))
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

int getResultFast(const vector<vector<char> > &board, bool white, bool legalMoves)
{
   /* bool echec = testCheck(board,white);
    if(echec && legalMoves)
        return 2;
    if(echec)
        return 1;*/
    if(!legalMoves && testCheck(board,white))
        return 1;
    if(!legalMoves)
        return 3;
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
    return 0;
}