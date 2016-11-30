#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include <ctype.h>

void ChessBoard::setupBoard() {
    pieces[0][0] = PAWNSTART & ALLWHITESTART;
    pieces[0][1] = ROOKSTART & ALLWHITESTART;
    pieces[0][2] = KNIGHTSTART & ALLWHITESTART;
    pieces[0][3] = BISHOPSTART & ALLWHITESTART;
    pieces[0][4] = QUEENSTART & ALLWHITESTART;
    pieces[0][5] = KINGSTART & ALLWHITESTART;

    pieces[1][0] = PAWNSTART & ALLBLACKSTART;
    pieces[1][1] = ROOKSTART & ALLBLACKSTART;
    pieces[1][2] = KNIGHTSTART & ALLBLACKSTART;
    pieces[1][3] = BISHOPSTART & ALLBLACKSTART;
    pieces[1][4] = QUEENSTART & ALLBLACKSTART;
    pieces[1][5] = KINGSTART & ALLBLACKSTART;

    AllWhitePieces = ALLWHITESTART;
    AllBlackPieces = ALLBLACKSTART;
    AllPieces = ALLWHITESTART|ALLBLACKSTART;
}

/**
 * Determines which piece is at loc
 * @param black true if it is a black piece
 * @param loc Bitboard with the position
 * @return index of piece
 */
short ChessBoard::findBoard(bool black, Bitboard loc) {
    short i;
    for (i=5; i>=0; i--) {
        if (pieces[!black][i] & loc) {
            break;
        }
    }
    return i;
}
