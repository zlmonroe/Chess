#include "check.h"
#include "ChessConstBitboards.h"
#include "MoveGenerator.h"
#include "ChessBoard.h"

Bitboard Check::getAllMoves(bool color) {
	Bitboard totalMoves = ChessConstBitboards::BLANK;
	int piece;
	Bitboard location;
	for (int i = 0; i < 64; i++) {
		location = 1 << i;
		piece = ChessBoard::findBoard(color, location);
		if (piece> 0) {
			switch (piece) {
			case 0:
				totalMoves = totalMoves || MoveGenerator::getPawnMoves(location, color);
				break;
			case 1:
				totalMoves = totalMoves || MoveGenerator::getRookMoves(location, color);
				break;
			case 2:
				totalMoves = totalMoves || MoveGenerator::getKnightMoves(location, color);
				break;
			case 3:
				totalMoves = totalMoves || MoveGenerator::getBishopMoves(location, color);
				break;
			case 4:
				totalMoves = totalMoves || MoveGenerator::getQueenMoves(location, color);
				break;
			case 5:
				totalMoves = totalMoves || MoveGenerator::getKingMoves(location, color);
				break;
			}
		}
	}
	return totalMoves;
}
Bitboard Check::getKingPos(bool color) {
	int piece;
	Bitboard location;
	for (int i = 0; i < 64; i++) {
		location = 1 << i;
		piece = ChessBoard::findBoard(color, location);
		if (piece = 5) {
			return location;
		}
	}
}
Bitboard Check::check(bool color) {
	return ((bool)(getKingPos(color) && getAllMoves(!color)));
}
