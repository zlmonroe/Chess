//
// Created by jon on 10/31/2016.
//

#include "MoveGenerator.h"

Bitboard MoveGenerator::getBishopMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getKightMoves(uint8_t position, bool isBlack) {
    Bitboard start = 1<<position;
    Bitboard clearA = COLUMNCLEAR[0];
    Bitboard clearAB = COLUMNCLEAR[0]&COLUMNCLEAR[1];
    Bitboard clearH = COLUMNCLEAR[7];
    Bitboard clearGH = COLUMNCLEAR[6]&COLUMNCLEAR[7];
    Bitboard own;
    if (isBlack)
        own = ALLBLACKSTART; //Switch to allBlackPieces when implemented
    else
        own = ALLWHITESTART; //Switch to allWhitePieces when implemented

    return ((((start&clearA)<<15)|((start&clearAB)<<6)|((start&clearAB)>>10)|((start&clearA)>>17)|((start&clearH)>>15)|((start&clearGH)>>6)|((start&clearGH)<<10)|(start&clearH)<<17)&~own);
}

Bitboard MoveGenerator::getKingMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getPawnMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getQueenMoves(uint8_t position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getRookMoves(uint8_t position, bool isBlack) {
    return 0;
}
Bitboard MoveGenerator::getAllMoves(bool color) {
	Bitboard totalMoves = ChessConstBitboards::BLANK;
	int piece;
	Bitboard location;
	for (int i = 0; i < 64; i++) {
		location = 1 << i;
		piece = ChessBoard::findBoard(color, location);
		if (piece> 0) {
			switch (piece) {
			case 0:
				totalMoves = totalMoves | MoveGenerator::getPawnMoves(location, color);
				break;
			case 1:
				totalMoves = totalMoves | MoveGenerator::getRookMoves(location, color);
				break;
			case 2:
				totalMoves = totalMoves | MoveGenerator::getKnightMoves(location, color);
				break;
			case 3:
				totalMoves = totalMoves | MoveGenerator::getBishopMoves(location, color);
				break;
			case 4:
				totalMoves = totalMoves | MoveGenerator::getQueenMoves(location, color);
				break;
			case 5:
				totalMoves = totalMoves | MoveGenerator::getKingMoves(location, color);
				break; //not necessary
			}
		}
	}
	return totalMoves;
}
