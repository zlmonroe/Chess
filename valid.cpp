#include <iostream>
#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include "valid.h"

bool MoveValidator::isValidMove(unsigned short userMove) {

    Bitboard valid_moves;

    short indexI = (userMove << 4) >> 12;
    short indexF = (userMove << 10) >> 10;
    short otherStuff = userMove >> 12;
    short color = userMove >> 15;
    short bStart = (Bitboard)1 << indexI
    short bEnd = (Bitboard)1 << indexF;

    piece = findBoard(color, bstart);

    switch (piece) {

case 0:

    valid_moves = getPawnMoves(color, bstart);
    break;

case 1:

    valid_moves = getRookMoves(color, bstart);
    break;

case 2:

    valid_moves = getKnightMoves(color, bstart);
    break;

case 3:

    valid_moves = getBishopMoves(color, bstart);
    break;

case 4:

    valid_moves = getQueenMoves(color, bstart);
    break;

case 5:

    valid_moves = getKingMoves(color, bstart);
    break;

default:

    std::cout<<"No piece found at that spot!"<<std::endl;
    valid_moves = 0x0000;

    }

    return (bEnd & valid_moves)(bool);
}
