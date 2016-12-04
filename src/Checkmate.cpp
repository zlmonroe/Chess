#include "MoveGenerator.h"
#include "ChessConstBitboards.h"


//color is the color of the defending piece
 bool MoveGenerator::check(bool color, ChessBoard* cb) {
 	return (bool)(cb[0].pieces[color][5] & getAllMoves(!color, cb));
 }

 bool MoveGenerator::checkmate1(bool color, Bitboard kingPos){//the color should be the color of the defending piece!
    //short i;
    //for(i=-1; kingPos; kingPos>>=1, i++)
     unsigned short i = 0;
     for(Bitboard b = 1ULL; kingPos ^ b; b <<= 1, i++);
	 return (bool)(getKingMoves(i,color,chessBoard)&~getAllMoves(!color, chessBoard));
 }

bool MoveGenerator::checkmate(bool color, ChessBoard* cb) {
	if (checkmate1(color, cb[0].pieces[color][5])) {
		return true;
	}
	else if (checkmate2(color, cb)) {
		return true;
	}
	return false;
}

bool MoveGenerator::checkmate2(bool color, ChessBoard*  cb){
	Bitboard attackingPiece;
	Bitboard attackingMove = 0;
	bool attackNotFound = true;
	Bitboard allMovesDefend = getAllMoves(color, chessBoard);
    unsigned short j = 0, i;
	for (i = 0; i < 5 && attackNotFound; i++) {
		Bitboard pieceBoard = cb[0].pieces[!color][i];
        j = 0;
		while (pieceBoard) {

			if (pieceBoard & 0b1) {

				switch (i) {
					case 0:
						if (cb[0].pieces[color][5] & getPawnMoves(j, !color, chessBoard)) {
							attackingPiece = cb[0].pieces[!color][0];
							attackNotFound = false;
						}
						break;
					case 1:
						if (cb[0].pieces[color][5] & getRookMoves(j, !color, chessBoard)) {
							attackingPiece = cb[0].pieces[!color][1];
							attackingMove = getRookMoves(i, !color, chessBoard);
							attackNotFound = false;
						}
						break;
					case 2:
						if (cb[0].pieces[color][5] & getKnightMoves(j, !color, chessBoard)) {
							attackingPiece = cb[0].pieces[!color][2];
							attackNotFound = false;
						}
						break;
					case 3:
						if (cb[0].pieces[color][5] & getBishopMoves(j, !color, chessBoard)) {
							attackingPiece = cb[0].pieces[!color][3];
							attackingMove = getBishopMoves(i, !color, chessBoard);
							attackNotFound = false;
						}
						break;
					case 4:
						if (cb[0].pieces[color][5] & getQueenMoves(j, !color, chessBoard)) {
							attackingPiece = cb[0].pieces[!color][4];
							attackingMove = getQueenMoves(i, !color, chessBoard);
							attackNotFound = false;
						}
						break;
					default:
						break;
				}
				j++;
				pieceBoard >>= 1;
			}
		}
	}
	if (attackingPiece & allMovesDefend) {
		return true;
	}
	else if(attackingMove) {
		int rowAttack = j / 8;
		int colAttack = j % 8;
		Bitboard kingLocation = cb[0].pieces[color][5];
        unsigned short k = 0;
		for (Bitboard b = 1ULL; kingLocation ^ b; b <<= 1, k++);
		int rowKing = k / 8;
		int colKing = k % 8;
		if (i == 1) {
			if (rowAttack == rowKing) {
				if (rowAttack < rowKing) {
					for (int l = rowAttack-1; l > 0; l--) {
						attackingMove & ROWCLEAR[l];
					}
				}
				else {
					for (int l = rowAttack + 1; l < 0; l++) {
						attackingMove & ROWCLEAR[l];
					}
				}
				for (int l = 0; l > colAttack; l++) {
					attackingMove & COLUMNCLEAR[l];
				}
				for (int l = 0; l < colAttack; l--) {
					attackingMove & COLUMNCLEAR[l];
				}
			}
			else {
				if (colAttack < colKing) {
					for (int l = colAttack - 1; l > 0; l--) {
						attackingMove & COLUMNCLEAR[l];
					}
				}
				else {
					for (int l = colAttack + 1; l < 0; l++) {
						attackingMove & COLUMNCLEAR[l];
					}
				}
				for (int l = 0; l > rowAttack; l++) {
					attackingMove & ROWCLEAR[l];
				}
				for (int l = 0; l < rowAttack; l--) {
					attackingMove & ROWCLEAR[l];
				}
			}
		}
		else {
			if (rowAttack < rowKing) {
				for (int l = rowAttack - 1; l > 0; l--) {
					attackingMove & ROWCLEAR[l];
				}
				for (int l = rowKing + 1; l < 0; l++) {
					attackingMove & ROWCLEAR[l];
				}
			}
			else if (rowAttack > rowKing) {
				for (int l = rowKing - 1; l > 0; l--) {
					attackingMove & ROWCLEAR[l];
				}
				for (int l = rowAttack + 1; l < 0; l++) {
					attackingMove & ROWCLEAR[l];
				}
			}
			if (colAttack < colKing) {
				for (int l = colAttack - 1; l > 0; l--) {
					attackingMove & COLUMNCLEAR[l];
				}
				for (int l = colKing + 1; l < 0; l++) {
					attackingMove & COLUMNCLEAR[l];
				}
			}
			else if (colAttack > colKing) {
				for (int l = colKing - 1; l > 0; l--) {
					attackingMove & COLUMNCLEAR[l];
				}
				for (int l = colAttack + 1; l < 0; l++) {
					attackingMove & COLUMNCLEAR[l];
				}
			}
		}
		return attackingMove & kingLocation;
	}

}
