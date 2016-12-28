#include <iostream>
#include <vector>

#include "board.h"

#define MASK       15ULL 

using namespace std;

typedef uint64_t board_type;

typedef struct {
   int row;
   int col;
} coor;

extern void *getEmptyBoard(void)
{
   return new uint64_t;
}

extern void printBoard(void *board)
{
   for (int row = 0; row < 4; row++)
   {
      for (int col = 0; col < 4; col++)
      {
         cout << pieceToChar(getPiece(board, row, col));
      }
      cout << "\n";
   }
}

extern char pieceToChar(int piece)
{
   if ( piece == B_QUEEN || piece == W_QUEEN )
      return 'Q';
   if (piece == B_KNIGHT || piece == W_KNIGHT)
      return 'N';
   if (piece == B_BISHOP || piece == W_BISHOP)
      return 'B';
   if (piece == W_ROOK || piece == B_ROOK)
      return 'R';
   else
      return '.';
}

extern color getColor(int piece)
{
   if (piece == B_QUEEN || piece == B_KNIGHT
    || piece == B_ROOK || piece == B_ROOK
     )
      return black;
   else
      return white;
}

extern void *copyBoard(void *board)
{
   board_type *tmp = new uint64_t;
   *tmp = *(board_type *)board;
   return tmp;
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

extern vector<void *> generateKnightMoves(void *board, int row, int col)
{
   vector <void *> ret ;
   color player;
   if ( getPiece(board, row, col) == W_KNIGHT)
      player = white;
   else if (getPiece(board, row, col) == B_KNIGHT)
      player = black;
   else
      return ret;

   board_type *tmp;
   tmp = (board_type *)copyBoard(board);
   setPiece((void *)tmp, row, col, EMPTY);
   vector <coor> coors;
   coors.push_back({row,col});
   coors.push_back({row - 2, col - 1});
   coors.push_back({row - 2, col + 1});
   coors.push_back({row + 2, col - 1});
   coors.push_back({row + 2, col + 1});
   coors.push_back({row - 1, col - 2});
   coors.push_back({row - 1, col + 2});
   coors.push_back({row + 1, col - 2});
   coors.push_back({row + 1, col + 2});
   for (vector <coor>::iterator it = coors.begin(); it != coors.end(); ++it)
   {
      if ( it->row < 0
        || it->row > 3
        || it->col < 0
        || it->col >3
         )
         continue;

      board_type *new_tmp = (board_type *)copyBoard(tmp);
      if (player == white)
         setPiece(new_tmp, it->row, it->col, W_KNIGHT);
      else
         setPiece(new_tmp, it->row, it->col, B_KNIGHT);
      ret.push_back(new_tmp);
   }
   return ret;
}

   

   




