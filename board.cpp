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

extern void resetBoard(void *board)
{
   *(board_type*)board = 0;
}

extern void printBoard(const void *board)
{
   for (int row = 0; row < 4; row++)
   {
      for (int col = 0; col < 4; col++)
      {
         cout << pieceToChar(getPiece(board, row, col));
      }
      cout << "\n";
   }
   cout << "\n";
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
    || piece == B_ROOK || piece == B_BISHOP
     )
      return black;
   else
      return white;
}

extern void *copyBoard(const void *board)
{
   board_type *tmp = new uint64_t;
   *tmp = *(board_type *)board;
   return tmp;
}

extern int getPiece( const void *board, int row, int col)
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

extern vector <void*> generateAllMoves(const void * board, color player_to_move)
{
   vector <void*> ret;
   int piece;

   if (player_to_move == white)
   {
      for (int row = 0; row < 4; row++)
      {
         for (int col = 0; col < 4; col++)
         {
            piece = getPiece(board, row, col);
            if (piece == EMPTY)
               continue;
            vector <void*> tmp_ret;

            switch (piece) {
               case W_ROOK:
                  tmp_ret = generateRookMoves(board, row, col);
                  break;

               case W_KNIGHT:
                  tmp_ret = generateKnightMoves(board, row, col);
                  break;

               case W_BISHOP:
                  tmp_ret = generateBishopMoves(board, row, col);
                  break;

               case W_QUEEN:
                  tmp_ret = generateQueenMoves(board, row, col);
                  break;
            }
            ret.insert(ret.end(), tmp_ret.begin(), tmp_ret.end());
         }
      }
   } else {
      for (int row = 0; row < 4; row++)
      {
         for (int col = 0; col < 4; col++)
         {
            piece = getPiece(board, row, col);
            if (piece == EMPTY)
               continue;
            vector <void*> tmp_ret;

            switch (piece) {
               case B_ROOK:
                  tmp_ret = generateRookMoves(board, row, col);
                  break;

               case B_KNIGHT:
                  tmp_ret = generateKnightMoves(board, row, col);
                  break;

               case B_BISHOP:
                  tmp_ret = generateBishopMoves(board, row, col);
                  break;

               case B_QUEEN:
                  tmp_ret = generateQueenMoves(board, row, col);
                  break;
            }
            ret.insert(ret.end(), tmp_ret.begin(), tmp_ret.end());
         }
      }
   }
   return ret;
}

extern int playerHasWon(void * board, color player)
{
   int ret = 1;
   int search_piece;

   if (player == black)
      search_piece = W_QUEEN;
   else
      search_piece = B_QUEEN;

   for (int row = 0; row < 4; row++)
   {
      for (int col = 0; col < 4; col ++)
      {
         if (getPiece(board, row, col) == search_piece)
         {
            ret = 0;
            break;
         }
      }
   }
   return ret;
}
         

extern vector<void *> generateKnightMoves(const void *board, int row, int col)
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
        || ( getPiece(tmp, it->row, it->col) != EMPTY
          && getColor(getPiece(tmp, it->row, it->col)) == player
           )
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

extern vector<void *> generateRookMoves(const void *board, int row, int col)
{
   vector <void *> ret;
   color player;
   if (getPiece(board, row, col) == W_ROOK)
      player = white;
   else if (getPiece(board, row, col) == B_ROOK)
      player = black;
   else
      return ret;

   board_type *tmp;
   tmp = (board_type *)copyBoard(board);
   setPiece((void*)tmp, row, col, EMPTY);
   vector<coor> coors;
   int tmp_row = row, tmp_col = col;
   int tmp_piece;
   do 
   {
      tmp_row -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row >0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while(tmp_col >0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   }while (tmp_col < 3 && tmp_piece == EMPTY);

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
         setPiece(new_tmp, it->row, it->col, W_ROOK);
      else
         setPiece(new_tmp, it->row, it->col, B_ROOK);
      ret.push_back(new_tmp);
   }
   return ret;
}

extern vector <void *> generateBishopMoves(const void *board, int row, int col)
{
   vector <void *> ret;
   color player;
   if (getPiece(board, row, col) == W_BISHOP)
      player = white;
   else if (getPiece(board, row, col) == B_BISHOP)
      player = black;
   else
      return ret;

   board_type *tmp;
   tmp = (board_type *)copyBoard(board);
   setPiece((void*)tmp, row, col, EMPTY);
   vector<coor> coors;
   int tmp_row = row, tmp_col = col;
   int tmp_piece;
   do 
   {
      tmp_row -= 1;
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row >0 && tmp_col > 0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row < 3 && tmp_col < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while(tmp_col >0 && tmp_row < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row -= 1;
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   }while (tmp_col < 3 && tmp_row > 0 && tmp_piece == EMPTY);

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
         setPiece(new_tmp, it->row, it->col, W_BISHOP);
      else
         setPiece(new_tmp, it->row, it->col, B_BISHOP);
      ret.push_back(new_tmp);
   }
   return ret;
}

extern vector <void *> generateQueenMoves(const void *board, int row, int col)
{
   vector <void *> ret;
   color player;
   if (getPiece(board, row, col) == W_QUEEN)
      player = white;
   else if (getPiece(board, row, col) == B_QUEEN)
      player = black;
   else
      return ret;

   board_type *tmp;
   tmp = (board_type *)copyBoard(board);
   setPiece((void*)tmp, row, col, EMPTY);
   vector<coor> coors;
   
   int tmp_row = row, tmp_col = col;
   int tmp_piece;
   do 
   {
      tmp_row -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row >0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while(tmp_col >0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   }while (tmp_col < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row -= 1;
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row >0 && tmp_col > 0 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while (tmp_row < 3 && tmp_col < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row += 1;
      tmp_col -= 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   } while(tmp_col >0 && tmp_row < 3 && tmp_piece == EMPTY);

   tmp_row = row, tmp_col = col;
   do 
   {
      tmp_row -= 1;
      tmp_col += 1;
      tmp_piece = getPiece(board, tmp_row, tmp_col);
      if (tmp_piece == EMPTY || getColor(tmp_piece) != player)
         coors.push_back({tmp_row, tmp_col});
   }while (tmp_col < 3 && tmp_row > 0 && tmp_piece == EMPTY);

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
         setPiece(new_tmp, it->row, it->col, W_QUEEN);
      else
         setPiece(new_tmp, it->row, it->col, B_QUEEN);
      ret.push_back(new_tmp);
   }
   return ret;
}

extern int recursiveSearchWhite(const void *board, int level)
{
   if (level == 0)
   {
      return BLACK_WINS;
   }

   vector <void*> moves = generateAllMoves(board, white);
   for (vector<void*>::iterator it = moves.begin(); it != moves.end(); ++it)
   {
      if (playerHasWon(*it, white) == 1)
         return WHITE_WINS;
   }

   for (vector<void*>::iterator it = moves.begin(); it != moves.end(); ++it)
   {
      if (recursiveSearchBlack(*it, level -1) == WHITE_WINS)
         return WHITE_WINS;
   }
   return BLACK_WINS;
}

extern int recursiveSearchBlack(const void *board, int level)
{
   if (level == 0)
      return BLACK_WINS;

   vector <void*> moves = generateAllMoves(board, black);
   for (vector<void*>::iterator it = moves.begin(); it != moves.end(); ++it)
   {
      if (playerHasWon(*it, black) == 1)
         return BLACK_WINS;
   }
   for (vector<void*>::iterator it = moves.begin(); it != moves.end(); ++it)
   {
      if (recursiveSearchWhite(*it, level -1) == BLACK_WINS)
         return BLACK_WINS;
   }
   return WHITE_WINS;
}
