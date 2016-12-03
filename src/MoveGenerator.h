//
// Created by jon on 10/31/2016.
//

#pragma once
#include "ChessConstBitboards.h"
#include "ChessBoard.h"

class MoveGenerator {
private:
    ChessBoard* chessBoard;
    bool checkmate1(bool color, Bitboard);
	bool checkmate2(bool color, ChessBoard*);

public:

    Bitboard getBishopMoves(unsigned short position, bool isBlack);
    Bitboard getKnightMoves(unsigned short position, bool isBlack);
    Bitboard getKingMoves(unsigned short position, bool isBlack);
    Bitboard getPawnMoves(unsigned short position, bool isBlack);
    Bitboard getQueenMoves(unsigned short position, bool isBlack);
    Bitboard getRookMoves(unsigned short position, bool isBlack);
    Bitboard getAllMoves(bool color);

    bool check(bool);
    bool checkmate(bool color, ChessBoard*);

    bool isValidMove(unsigned short userMove);
    void uncheckedMove(bool, short, unsigned short,unsigned short);
    MoveGenerator(ChessBoard* chessBoard) {this->chessBoard=chessBoard;}
    MoveGenerator(){};
};


