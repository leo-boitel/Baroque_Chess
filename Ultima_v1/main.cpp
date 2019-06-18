/*
TODO :
    -Graphic support ? SFML
    -Minmax to test
*/
#define NDEBUG
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <SFML/Graphics.hpp>
//#include <cassert>

#include "mcts.h"

//#include "possibleMoves.h"
//#include "board.h"

using namespace std;

/*
Board coding : b[0][7] = square a8
White pieces in caps
P = pawn
I = Immobilizer
C = Coordinator
K = King
W = Withdrawer
L = Long-Leaper
B = Imitator (B for bishop)
_ = empty

Ex : b[2][3] = p <=> Black pawn in c4
*/
const int mcts_depth = 100;
const double BoardState::bias = 0.3;

int main()
{
    srand(time(0));
    int squareSize = 100;
    float scale = ((float)squareSize)/60;
    sf::Vector2f vscale(scale,scale);
    sf::Color w(255,205,160);
    sf::Color b(210,140,70);
    sf::Color sel(235,170,110);

    // bool castleW(false), castleB(false),swapRookW(false),swapRookB(false); // symetries, a passer a genBoard()
    vector< vector<char> > board = genBoard();
    bool trait(true);


    sf::RenderWindow window(sf::VideoMode(8*squareSize, 8*squareSize), "Baroque Chess");


    sf::RectangleShape black(sf::Vector2f(squareSize, squareSize));
    sf::RectangleShape white(sf::Vector2f(squareSize, squareSize));
    sf::RectangleShape selected(sf::Vector2f(squareSize, squareSize));
    black.setFillColor(b);
    white.setFillColor(w);
    selected.setFillColor(sel);
    sf::Texture tpb;
        tpb.loadFromFile("Images/pb.png");
        sf::Sprite pb(tpb);
        pb.setScale(vscale);
        sf::Texture tpw;
        tpw.loadFromFile("Images/pw.png");
        sf::Sprite pw(tpw);
        pw.setScale(vscale);
        sf::Texture tww;
        tww.loadFromFile("Images/ww.png");
        sf::Sprite ww(tww);
        ww.setScale(vscale);
        sf::Texture twb;
        twb.loadFromFile("Images/wb.png");
        sf::Sprite wb(twb);
        wb.setScale(vscale);
        sf::Texture tkw;
        tkw.loadFromFile("Images/kw.png");
        sf::Sprite kw(tkw);
        kw.setScale(vscale);
        sf::Texture tkb;
        tkb.loadFromFile("Images/kb.png");
        sf::Sprite kb(tkb);
        kb.setScale(vscale);
        sf::Texture tiw;
        tiw.loadFromFile("Images/iw.png");
        sf::Sprite iw(tiw);
        iw.setScale(vscale);
        sf::Texture tib;
        tib.loadFromFile("Images/ib.png");
        sf::Sprite ib(tib);
        ib.setScale(vscale);
        sf::Texture tcb;
        tcb.loadFromFile("Images/cb.png");
        sf::Sprite cb(tcb);
        cb.setScale(vscale);
        sf::Texture tcw;
        tcw.loadFromFile("Images/cw.png");
        sf::Sprite cw(tcw);
        cw.setScale(vscale);
        sf::Texture tbb;
        tbb.loadFromFile("Images/bb.png");
        sf::Sprite bb(tbb);
        bb.setScale(vscale);
        sf::Texture tbw;
        tbw.loadFromFile("Images/bw.png");
        sf::Sprite bw(tbw);
        bw.setScale(vscale);
        sf::Texture tlb;
        tlb.loadFromFile("Images/lb.png");
        sf::Sprite lb(tlb);
        lb.setScale(vscale);
        sf::Texture tlw;
        tlw.loadFromFile("Images/lw.png");
        sf::Sprite lw(tlw);
        lw.setScale(vscale);

    chrono::time_point<chrono::system_clock> cstart, cend; 
    int selectedX = -1, selectedY = -1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type==sf::Event::KeyPressed)
            {
                vector<tmove> p = possibleMoves(board,trait);
                cstart = chrono::system_clock::now();
                board = doMove(board,BoardState::mcPlay(board,trait,mcts_depth));
                cend = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = cend - cstart; 
                cout<<"Time to play : "<<elapsed_seconds.count()<<"s"<<endl;
                trait = !trait;
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
            	if(selectedX==-1)
            	{
            		selectedX = event.mouseButton.x/squareSize;
            		selectedY = event.mouseButton.y/squareSize;
            	}
            	else
            	{
            		if(!tryMove(board,trait,selectedX,selectedY,(event.mouseButton.x/squareSize),(event.mouseButton.y/squareSize)))
                        cout<<"Invalid move"<<endl;
                    selectedX = -1;
                    selectedY = -1;
            	}
            }
        }
        // window.clear(sf::Color::Black); //useless si on remplit
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(i==selectedX && j == selectedY)
                {
                    selected.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                    window.draw(selected);
                }
                else if((i+j)%2==0)
                {
                    white.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                    window.draw(white);
                }
                else
                {
                    black.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                    window.draw(black);
                }
                switch(board[i][j])
                {
                    case 'p':
                        pb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(pb);
                        break;
                    case 'P':
                        pw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(pw);
                        break;
                    case 'W':
                        ww.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(ww);
                        break;
                    case 'w':
                        wb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(wb);
                        break;
                    case 'K':
                        kw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(kw);
                        break;
                    case 'k':
                        kb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(kb);
                        break;
                    case 'I':
                        iw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(iw);
                        break;
                    case 'i':
                        ib.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(ib);
                        break;
                    case 'c':
                        cb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(cb);
                        break;
                    case 'C':
                        cw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(cw);
                        break;
                    case 'b':
                        bb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(bb);
                        break;
                    case 'B':
                        bw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(bw);
                        break;
                    case 'l':
                        lb.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(lb);
                        break;
                    case 'L':
                        lw.setPosition(sf::Vector2f(i*squareSize,j*squareSize));
                        window.draw(lw);
                        break;
                }

            }
        }

        window.display();
        sf::sleep(sf::milliseconds(500));
    }
   /* string a;
    srand(time(0));
    vector< vector<char> > board = genBoard();
    bool white = true;
    vector<vector<vector<char> > > p = possibleMoves(board,white);
    while (true)
    {
        printBoard(board);
        cout<<endl<<endl<<endl;
        //cin>>a;
        askMoveConsole(board,white);
        //p = possibleMoves(board,white);
    }
    cout<<"Game over !"<<endl;*/
    return 0;
}
