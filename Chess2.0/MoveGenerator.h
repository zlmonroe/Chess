//
// Created by jon on 10/31/2016.
//


#include "ChessConstBitboards.h"
#include "ChessBoard.h"

class MoveGenerator {
private:
    ChessBoard* chessBoard;

public:
    Bitboard getBishopMoves(uint8_t position, bool isBlack);
    Bitboard getKnightMoves(uint8_t position, bool isBlack);
    Bitboard getKingMoves(uint8_t position, bool isBlack);
    Bitboard getPawnMoves(uint8_t position, bool isBlack);
    Bitboard getQueenMoves(uint8_t position, bool isBlack);
    Bitboard getRookMoves(uint8_t position, bool isBlack);
    bool isValidMove(unsigned short userMove);
    void uncheckedMove(bool, short, uint8_t,uint8_t);
    MoveGenerator(ChessBoard* chessBoard) {this->chessBoard=chessBoard;}
};


