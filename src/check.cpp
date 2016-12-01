#include "check.h"
 #include "ChessConstBitboards.h"
 #include "MoveGenerator.h"
 #include "ChessBoard.h"

Check::Check(MoveGenerator m){
  moves = m;
}
 Bitboard Check::check(bool color) {
 	return ((bool)(ChessBoard::pieces[color][5] & moves.getAllMoves(!color)));
 }
