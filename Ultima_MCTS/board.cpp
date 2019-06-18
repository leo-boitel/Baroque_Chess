#include "board.h"
#include "possibleMoves.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


//sf::Texture getEmptyBoard


bool tryMove(vector< vector<char> > &board, bool &white, int x, int y, int xd, int yd)
{
    if(x>=0 && x<8 && y>=0 && y<8 && xd>=0 && xd<8 && yd>=0 && yd<8)
    {
        char piece = board[x][y];
        if(piece != board[xd][yd])
        {
            vector<vector<vector<char> > > p(0);
            pair<int,int> roi = findKing(board,white);
            possibleMovesPiece(p,board,x,y,roi.first,roi.second,white);
            for(size_t i=0;i<p.size();i++)
            {
                if(p[i][xd][yd] == piece && !testCheck(p[i],white))
                {
                    board = p[i];
                    white = !white;
                    int code = getResult(board,white);
                    switch(code)
                    {
                        case 1:
                            cout<<"Mat !"<<endl; return true;
                        case 2:
                            cout<<"Echec !"<<endl; return true;
                        case 3:
                            cout<<"Pat !"<<endl; return true;
                        case -1:
                            cout<<"Erreur : pas de roi !"<<endl;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void printBoard(vector< vector<char> > &board)
{
    for(int i=7;i>=0;i--)
    {
        for(int j=0;j<8;j++)
            cout<<board[j][i]<<" ";
        cout<<endl;
    }
}

vector< vector<char> > genBoard(bool castleW, bool castleB, bool swapRookW, bool swapRookB)
{
    vector< vector<char> > b(8,vector<char>(8,'_'));
    for(int i=0;i<8;i++)
    {
        b[i][1] = 'P';
        b[i][6] = 'p';
    }
    if(castleW)
    {
        b[4][0] = 'K';
        b[3][0] = 'W';
    }
    else
    {
        b[3][0] = 'K';
        b[4][0] = 'W';
    }
    if(castleB)
    {
        b[3][7] = 'k';
        b[4][7] = 'w';
    }
    else
    {
        b[4][7] = 'k';
        b[3][7] = 'w';
    }
    if(swapRookW)
    {
        b[7][0] = 'I';
        b[0][0] = 'C';
    }
    else
    {
        b[0][0] = 'I';
        b[7][0] = 'C';
    }
    if(swapRookB)
    {
        b[0][7] = 'i';
        b[7][7] = 'c';
    }
    else
    {
        b[7][7] = 'i';
        b[0][7] = 'c';
    }
    b[1][0] = 'L';
    b[6][0] = 'L';
    b[1][7] = 'l';
    b[6][7] = 'l';
    b[2][0] = 'B';
    b[5][0] = 'B';
    b[2][7] = 'b';
    b[5][7] = 'b';

    return b;
}

void askMoveConsole(vector<vector<char> > &board, bool &white)
{
    int x,y,xd,yd;
    cout<<"x puis y depart ?"<<endl;
    cin>>x;
    cin>>y;
    cout<<"x puis y arrivee ?"<<endl;
    cin>>xd;
    cin>>yd;
    if(!tryMove(board, white, x, y, xd, yd))
        cout<<"\n------ INVALID MOVE -----------\n"<<endl;
}
