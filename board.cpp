
#include "board.h"

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
