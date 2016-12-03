#include "MoveGenerator.h"
#include "ChessConstBitboards.h"

//color is the color of the defending piece
 bool MoveGenerator::check(bool color) {
 	return ((bool)(chessBoard[0].pieces[color][5] & getAllMoves(!color)));
 }

 bool MoveGenerator::checkmate1(bool color, Bitboard kingPos){//the color should be the color of the defending piece!
    short i;
    for(i=-1; kingPos; kingPos>>=1, i++)
	return (bool)(getKingMoves(i,color)&~getAllMoves(!color));
 }

bool MoveGenerator::checkmate(bool color, ChessBoard* c) {
	if (checkmate1(color, c[0].pieces[color][5])) {
		return false;
	}
	else if (checkmate2(color, c)) {
		return false;
	}
	return true;
}

bool MoveGenerator::checkmate2(bool color, ChessBoard*  c){
	Bitboard attackingPiece;
	Bitboard attackingMove = 0;
	bool attackNotFound = true;
	Bitboard allMovesDefend = getAllMoves(color);
	int i=0;
	while (i < 5 && attackNotFound) {
		Bitboard pieceBoard = c[0].pieces[!color][i];
		unsigned short j;
		while (pieceBoard) {
			if ((pieceBoard & 0b1) == 0b1) {
				switch (i) {
				case 0:
					if (c[0].pieces[color][5] & getPawnMoves(j, !color)) {
						attackingPiece = c[0].pieces[!color][0];
						bool attackNotFound = false;
					}
					break;
				case 1:
					if (c[0].pieces[color][5] & getRookMoves(j, !color)) {
						attackingPiece = c[0].pieces[!color][1];
						attackingMove = getRookMoves(i, !color);
						bool attackNotFound = false;
					}
					break;
				case 2:
					if (c[0].pieces[color][5] & getKnightMoves(j, !color)) {
						attackingPiece = c[0].pieces[!color][2];
						bool attackNotFound = false;
					}
					break;
				case 3:
					if (c[0].pieces[color][5] & getBishopMoves(j, !color)) {
						attackingPiece = c[0].pieces[!color][3];
						attackingMove = getBishopMoves(i, !color);
						bool attackNotFound = false;
					}
					break;
				case 4:
					if (c[0].pieces[color][5] & getQueenMoves(j, !color)) {
						attackingPiece = c[0].pieces[!color][4];
						attackingMove = getQueenMoves(i, !color);
						bool attackNotFound = false;
					}
					break;
				}
				j++;
				pieceBoard >> 1;
			}
		}
	}
	if (attackingPiece & allMovesDefend) {
		return true;
	}
	else if(attackingMove) {
		int rowAttack = i / 8;
		int colAttack = i % 8;
		short k;
		Bitboard kingLocationTemp = c[0].pieces[color][5];
		Bitboard kingLocation = c[0].pieces[color][5];
		for (k = -1; kingLocationTemp; kingLocationTemp >>= 1, k++);
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
