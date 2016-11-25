#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include "valid.h"

Bitboard getBishopMoves(short color, Bitboard bStart) {
    int pos=0;
    while (bStart) {
        bStart = bStart >> 1;
        pos++;
    }
    pos-=1;

    Bitboard AllPieces = 0b1000000000;

    Bitboard bArray = ((AllPieces & BOccupancy[pos]) * BMagic[pos]) >> (64-BBits[pos]);
    std::cout << bArray;
}
