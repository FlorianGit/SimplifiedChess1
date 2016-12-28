#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <stdint.h>
#include <vector>


#define EMPTY       0
#define W_QUEEN     1
#define W_ROOK      2
#define W_BISHOP    3
#define W_KNIGHT    4LL
#define B_QUEEN     5
#define B_ROOK      6
#define B_BISHOP    7
#define B_KNIGHT    8LL

using namespace std;

typedef enum {white = 0, black = 1} color;

extern void *getEmptyBoard(void);
extern void printBoard(void *board);
extern void *copyBoard(void *board);
extern int getPiece(void *board, int row, int col);
extern void setPiece(void *board, int row, int col, int piece);

extern vector<void *> generateKnightMoves(void *board, int row, int col);

#endif
