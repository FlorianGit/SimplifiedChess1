#include <iostream>

#include "board.h"

using namespace std;

int main()
{
   int nof_games, nof_w_pieces, nof_b_pieces, nof_moves;
   cin >> nof_games;
   for (int game_index = 0; game_index < nof_games; game_index++)
   {
      void *board = getEmptyBoard();
      cin >> nof_w_pieces >> nof_b_pieces >> nof_moves;
      for (int index = 0; index < nof_w_pieces; index++)
      {
         char t, char_col;
         int piece, col, row;
         cin >> t >> char_col >> row;
         switch (t)
         {
            case 'Q':
               piece = W_QUEEN;
               break;

            case 'N':
               piece = W_KNIGHT;
               break;

            case 'B':
               piece = W_BISHOP;
               break;

            case 'R':
               piece = W_ROOK;
               break;
         }
         col = (int)char_col - 'A';
         row = 4 - row;
         setPiece(board, row, col, piece);
      }
      for (int index = 0; index < nof_b_pieces; index++)
      {
         char t, char_col;
         int piece, col, row;
         cin >> t >> char_col >> row;
         switch (t)
         {
            case 'Q':
               piece = B_QUEEN;
               break;

            case 'N':
               piece = B_KNIGHT;
               break;

            case 'B':
               piece = B_BISHOP;
               break;

            case 'R':
               piece = B_ROOK;
               break;
         }
         col = (int)char_col - 'A';
         row = 4 - row;
         setPiece(board, row, col, piece);
      }
      printBoard(board);
   }
   return 0;
}

