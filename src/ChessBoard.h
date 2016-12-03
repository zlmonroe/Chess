#pragma once
#include "ChessConstBitboards.h"
#include <iostream>


class ChessBoard {
public:
	ChessBoard();
	ChessBoard(const ChessBoard*);

	/* The white piece positions */
	//WhitePawns,WhiteRooks, WhiteKnights, WhiteBishops, WhiteQueens, WhiteKing

	/* The black piece positions */
	//BlackPawns,BlackRooks, BlackKnights, BlackBishops, BlackQueens, BlackKing

	// Bitboard containing white pieces at [0] and black pieces at [1]
	Bitboard pieces[2][6];

	/* Commonly derived positions */
	Bitboard Enpessant[2];
	Bitboard AllWhitePieces;
	Bitboard AllBlackPieces;
	Bitboard AllPieces;
	short getRowFromChar(char letter);
	bool queryPiece(char column,short row, Bitboard board);

    Bitboard* getWhitePieces() {return pieces[0];}
    Bitboard* getBlackPieces() {return pieces[1];}
	void setupBoard();
	short findBoard(bool black, Bitboard loc);
};
