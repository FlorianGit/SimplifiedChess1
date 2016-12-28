#include <iostream>

#include "board.h"

using namespace std;

int main()
{
   board_type board = 0LL;
   setPiece((void*)&board, 1,1, B_KNIGHT);
   setPiece((void*)&board, 3,2, W_KNIGHT);
   cout << board << "\n";
   cout << getPiece((void*)&board, 3,2) << "\n";
   cout << getPiece((void*)&board, 1,1) << "\n";
   return 0;
}

