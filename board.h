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

#define WHITE_WINS  0
#define BLACK_WINS  1

using namespace std;

typedef enum {white = 0, black = 1} color;

extern void *getEmptyBoard(void);
extern char pieceToChar(int piece);
extern color getColor(int piece);
extern void printBoard(const void *board);
extern void *copyBoard(const void *board);
extern int getPiece(const void *board, int row, int col);
extern void setPiece(void *board, int row, int col, int piece);

extern vector <void*> generateAllMoves(const void * board, color player_to_move);
extern vector<void *> generateKnightMoves(const void *board, int row, int col);
extern vector<void *> generateRookMoves(const void *board, int row, int col);
extern vector <void *> generateBishopMoves(const void *board, int row, int col);
extern vector <void *> generateQueenMoves(const void *board, int row, int col);

extern int playerHasWon(void * board, color player);
extern int recursiveSearchWhite(const void *board, int level);
extern int recursiveSearchBlack(const void *board, int level);
#endif
