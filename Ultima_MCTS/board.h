#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <vector>

bool tryMove(std::vector< std::vector<char> > &board, bool &white, int x, int y, int xd, int yd);
std::vector<std::vector<char> > genBoard(bool castleW = true, bool castleB = true, bool swapRookW = true, bool swapRookB = true);
void printBoard(std::vector< std::vector<char> > &board);
void askMoveConsole(std::vector<std::vector<char> > &board, bool &white);


#endif // BOARD_H_INCLUDED
