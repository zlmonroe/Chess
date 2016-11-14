//
// Created by jon on 10/31/2016.
//

#include "MoveGenerator.h"

Bitboard MoveGenerator::getBishopMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getKightMoves(uint8_t position, bool isBlack) {
    Bitboard start = 1<<position;
    Bitboard clearA = COLUMNCLEAR[0];
    Bitboard clearAB = COLUMNCLEAR[0]&COLUMNCLEAR[1];
    Bitboard clearH = COLUMNCLEAR[7];
    Bitboard clearGH = COLUMNCLEAR[6]&COLUMNCLEAR[7];
    Bitboard own;
    if (isBlack)
        own = ALLBLACKSTART;
    else
        own = ALLWHITESTART;

    return ((((start&clearA)<<15)|((start&clearAB)<<6)|((start&clearAB)>>10)|((start&clearA)>>17)|((start&clearH)>>15)|((start&clearGH)>>6)|((start&clearGH)<<10)|(start&clearH)<<17)&!own);
}

Bitboard MoveGenerator::getKingMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getPawnMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getQueenMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getRookMoves(uint8_t position, bool isBlack) {
    return 0;
}
