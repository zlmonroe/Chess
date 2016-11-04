//
// Created by jon on 10/31/2016.
//

#ifndef CHESS_MOVEVALIDATOR_H
#define CHESS_MOVEVALIDATOR_H


#include "ChessConstBitboards.h"

class MoveValidator {
private:

public:
    Bitboard getBishopMoves(uint8_t position);
    Bitboard getKightMoves(uint8_t position);
    Bitboard getKingMoves(uint8_t position);
    Bitboard getPawnMoves(uint8_t position);
    Bitboard getQueenMoves(uint8_t position);
    Bitboard getRookMoves(uint8_t position);
};


#endif //CHESS_MOVEVALIDATOR_H
