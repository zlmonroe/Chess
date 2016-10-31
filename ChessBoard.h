#include "ChessConstBitboards.h"
#include <iostream>
#include <bitset>

class ChessBoard {
private:
	/* The white piece positions */
	//WhitePawns,WhiteRooks, WhiteKnights, WhiteBishops, WhiteQueens, WhiteKing

	/* The black piece positions */
	//BlackPawns,BlackRooks, BlackKnights, BlackBishops, BlackQueens, BlackKing

	// Bitboard containing white pieces at [0] and black pieces at [1]
	Bitboard pieces[2][6];

	/* Commonly derived positions */
	Bitboard AllWhitePieces;
	Bitboard AllBlackPieces;
	Bitboard AllPieces;
	short getRowFromChar(char letter);
	bool queryPiece(char column,short row, Bitboard board);

public:
    std::bitset<64> printableBitboard(Bitboard board);
    Bitboard* getWhitePieces() {return pieces[0];}
    Bitboard* getBlackPieces() {return pieces[1];}
	void setupBoard();
	char* userInput();
	uint8_t findBoard(bool white, char* pos);

	Bitboard valid(Bitboard loc, short piece, bool white);

};
