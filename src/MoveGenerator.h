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

    Bitboard getBishopMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getKnightMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getKingMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getPawnMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getQueenMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getRookMoves(unsigned short position, bool isBlack, ChessBoard*);
    Bitboard getAllMoves(bool color, ChessBoard*);

    bool check(bool, ChessBoard*);
    bool checkmate(bool color, ChessBoard*);

    bool isValidMove(unsigned short userMove);
    void uncheckedMove(bool, short, unsigned short,unsigned short, ChessBoard*);
    MoveGenerator(ChessBoard* chessBoard) {this->chessBoard=chessBoard;}
    MoveGenerator(){};
};


