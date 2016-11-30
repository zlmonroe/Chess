#include "check.h"
 #include "ChessConstBitboards.h"
 #include "MoveGenerator.h"
 #include "ChessBoard.h"

Check::Check(MoveGenerator m){
  moves = m;
}
 Bitboard Check::getAllMoves(bool color) {
 	Bitboard totalMoves = BLANK;
 	int piece;
 	Bitboard location;
 	for (int i = 0; i < 64; i++) {
 		location = 1 << i;
 		piece = moves.chessBoard[0].findBoard(color, location);
 		if (piece> 0) {
 			switch (piece) {
 			case 0:
 				totalMoves = totalMoves | moves.getPawnMoves(location, color);
 				break;
 			case 1:
 				totalMoves = totalMoves | moves.getRookMoves(location, color);
 				break;
 			case 2:
 				totalMoves = totalMoves | moves.getKnightMoves(location, color);
 				break;
 			case 3:
 				totalMoves = totalMoves |moves.getBishopMoves(location, color);
 				break;
 			case 4:
 				totalMoves = totalMoves | moves.getQueenMoves(location, color);
  				break;
  			case 5:
  				totalMoves = totalMoves | moves.getKingMoves(location, color);
 				break;
 				break; //not necessary
  			}
  		}
  	}
 	return totalMoves;
 }
 Bitboard Check::check(bool color) {
 	return ((bool)(ChessBoard::pieces[color][5] & getAllMoves(!color)));
 }
