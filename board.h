#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <stdint.h>

typedef uint64_t board_type;

#define EMPTY       0
#define W_QUEEN     1
#define W_ROOK      2
#define W_BISHOP    3
#define W_KNIGHT    4LL
#define B_QUEEN     5
#define B_ROOK      6
#define B_BISHOP    7
#define B_KNIGHT    8LL
#define MASK       15ULL 

typedef enum {white = 0, black = 1} color;

extern int getPiece(void *board, int row, int col);
extern void setPiece(void *board, int row, int col, int piece);


#endif
