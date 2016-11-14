//
// Created by jon on 10/31/2016.
//

#ifndef CHESS_MOVEVALIDATOR_H
#define CHESS_MOVEVALIDATOR_H


#include "ChessConstBitboards.h"

class MoveGenerator {
private:

public:
    Bitboard getBishopMoves(uint8_t position, bool isBlack);
    Bitboard getKightMoves(uint8_t position, bool isBlack);
    Bitboard getKingMoves(uint8_t position, bool isBlack);
    Bitboard getPawnMoves(uint8_t position, bool isBlack);
    Bitboard getQueenMoves(uint8_t position, bool isBlack);
    Bitboard getRookMoves(uint8_t position, bool isBlack);
};


#endif //CHESS_MOVEVALIDATOR_H
