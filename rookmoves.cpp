#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include "valid.h"

Bitboard getRookMoves(short color, Bitboard bStart) {
    int pos=0;
    while (bStart) {
        bStart = bStart >> 1;
        pos++;
    }
    pos-=1;

    Bitboard AllPieces = 0b1000000000;

    Bitboard bArray = ((AllPieces & ROccupancy[pos]) * RMagic[pos]) >> (64-RBits[pos]);
    std::cout << bArray << std::endl;
}
