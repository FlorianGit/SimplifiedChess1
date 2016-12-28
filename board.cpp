#include <iostream>

#include "board.h"

#define MASK       15ULL 

using namespace std;

typedef uint64_t board_type;

extern void *getEmptyBoard(void)
{
   return new uint64_t;
}

extern void printBoard(void *board)
{
   cout << *(board_type*)board << "\n";
}

extern int getPiece(void *board, int row, int col)
{
   board_type *brd = (board_type*)board;
   return (*brd >> (4 * (row * 4 + col))) & MASK;
}
   
extern void setPiece(void *board, int row, int col, int piece)
{
   board_type *brd = (board_type*)board;
   *brd &= ~(MASK << (4 * (row * 4 + col)));
   *brd |= (uint64_t)piece << (4 * (row * 4 + col));
}
