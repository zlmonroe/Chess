//
// Created by jon on 10/31/2016.
//


#include "ChessConstBitboards.h"
#include "ChessBoard.h"

class MoveGenerator {
private:
    ChessBoard* chessBoard;

public:
    Bitboard getBishopMoves(unsigned short position, bool isBlack);
    Bitboard getKnightMoves(unsigned short position, bool isBlack);
    Bitboard getKingMoves(unsigned short position, bool isBlack);
    Bitboard getPawnMoves(unsigned short position, bool isBlack);
    Bitboard getQueenMoves(unsigned short position, bool isBlack);
    Bitboard getRookMoves(unsigned short position, bool isBlack);
    Bitboard getAllMoves(bool color);
    bool isValidMove(unsigned short userMove);
    void uncheckedMove(bool, short, unsigned short,unsigned short);
    MoveGenerator(ChessBoard* chessBoard) {this->chessBoard=chessBoard;}
};


