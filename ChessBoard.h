#include "ChessConstBitboards.h"
#include <iostream>
#include <bitset>

class ChessBoard {
private:
	/* The white piece positions */
	//WhitePawns,WhiteRooks, WhiteKnights, WhiteBishops, WhiteQueens, WhiteKing
	Bitboard WhitePieces[6];

	/* The black piece positions */
	//BlackPawns,BlackRooks, BlackKnights, BlackBishops, BlackQueens, BlackKing
	Bitboard BlackPieces[6];

	/* Commonly derived positions */
	Bitboard AllWhitePieces;
	Bitboard AllBlackPieces;
	Bitboard AllPieces;
	short getRowFromChar(char letter);
	bool queryPiece(char column,short row, Bitboard board);

public:
    std::bitset<64> printableBitboard(Bitboard board);
    Bitboard* getWhitePieces() {return WhitePieces;}
    Bitboard* getBlackPieces() {return BlackPieces;}
	void setupBoard();
	char* userInput();
	short findBoard(bool white, char* pos);

	Bitboard valid(Bitboard loc, short piece, bool white);

};
