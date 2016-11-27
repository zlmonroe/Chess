#include "check.h"
#include "ChessConstBitboards.h"
#include "MoveGenerator.h"
#include "ChessBoard.h"

Bitboard Check::check(bool color) {
	return ((bool)(ChessBoard::pieces[color][5] & MoveGenerator::getAllMoves(!color)));
}
