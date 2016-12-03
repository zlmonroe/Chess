#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include <ctype.h>

ChessBoard::ChessBoard(){};

ChessBoard::ChessBoard(const ChessBoard* cb) {
    //copy pieces
    for (short i = 0; i < 2; i++) {
        for (short j = 0; j < 6; j++) {
            pieces[i][j] = cb[0].pieces[i][j];
        }
    }
    //copy Allwhite
    AllWhitePieces = cb[0].AllWhitePieces;
    //copy AllBlack
    AllBlackPieces = cb[0].AllBlackPieces;
    //Copy AllPieces
    AllPieces = cb[0].AllPieces;
}

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
        if (pieces[black][i] & loc) {
            break;
        }
    }
    return i;
}
