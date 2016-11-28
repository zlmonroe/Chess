//
// Created by jon on 10/31/2016.
//

#include "MoveGenerator.h"
#include "magics.h"
#include "ChessConstBitboards.h"
#include "Chessboard.h"
#include <bitset>



Bitboard MoveGenerator::getBishopMoves(uint8_t pos, bool isBlack) {
    pos--;

    Bitboard bArray = ((chessBoard[0].AllPieces & BOccupancy[pos]) * BMagic[pos]) >> (64-BBits[pos]);
    std::cout << bArray;
    return 1;
}

Bitboard MoveGenerator::getKnightMoves(uint8_t position, bool isBlack) {
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
    Bitboard pos = (Bitboard)(1<<position);

    Bitboard left_attack;
    Bitboard right_attack;
    Bitboard pawn_one_forward;
    Bitboard pawn_two_forward;
    Bitboard all_moves_possible;

    if (!isBlack) {
                left_attack = ((COLUMNCLEAR[0] & pos) << 7) & (chessBoard[0].AllBlackPieces | chessBoard[0].Enpessant[0]);
                right_attack = ((COLUMNCLEAR[7] & pos) << 9) & (chessBoard[0].AllBlackPieces | chessBoard[0].Enpessant[0]);
                pawn_one_forward = ((pos << 8) & ~(chessBoard[0].AllPieces));
                pawn_two_forward = (((((pos & ROWMASK[1]) << 8) & ~chessBoard[0].AllPieces)<<8) & ~chessBoard[0].AllPieces);
    }
    else {
                left_attack = ((COLUMNCLEAR[0] & pos) >> 9) & (chessBoard[0].AllWhitePieces | chessBoard[0].Enpessant[1]);
                right_attack = ((COLUMNCLEAR[7] & pos) >> 7) & (chessBoard[0].AllWhitePieces | chessBoard[0].Enpessant[1]);
                pawn_one_forward = ((pos >> 8) & ~(chessBoard[0].AllPieces));
                pawn_two_forward = ((((pos & ROWMASK[7]) >> 8) & ~(chessBoard[0].AllPieces) >> 8) & ~(chessBoard[0].AllPieces));

    }
    all_moves_possible = (left_attack | right_attack | pawn_one_forward | pawn_two_forward);
    return all_moves_possible;
}

Bitboard MoveGenerator::getRookMoves(uint8_t pos, bool isBlack) {
    pos--;

    Bitboard bArray = ((chessBoard[0].AllPieces & ROccupancy[pos]) * RMagic[pos]) >> (64-RBits[pos]);
    std::cout << bArray << std::endl;
    return 1;
}


Bitboard MoveGenerator::getQueenMoves(uint8_t position, bool isBlack) {
    return 0;
}

bool MoveGenerator::isValidMove(unsigned short userMove) {

    Bitboard valid_moves;
    unsigned short bStart = (userMove & 0b0000111111000000)>>6;
    unsigned short bEnd = (userMove & 0b111111);
    unsigned short otherStuff = (userMove & 0b0111000000000000) >>12;
    bool color = (userMove & 0b1000000000000000)>>15;
    short piece = chessBoard[0].findBoard(!color, (Bitboard)1<<bStart);

    if (piece>=0) std::cout << "Found " << PIECE_NAMES[piece] << "\n";
    else {std::cout << "No piece found" << std::endl;}
    switch (piece) {

case 0:

    valid_moves = getPawnMoves(bStart, color);
    break;

case 1:

    valid_moves = getRookMoves(bStart, color);
    break;

case 2:

    valid_moves = getKnightMoves(bStart, color);
    break;

case 3:

    valid_moves = getBishopMoves(bStart, color);
    break;

case 4:

    valid_moves = getQueenMoves(bStart, color);
    break;

case 5:

    valid_moves = getKingMoves(bStart, color);
    break;

default:

    std::cout<<"No piece found at that spot!"<<std::endl;
    valid_moves = (Bitboard)0x0000;

    }
    if ((bool)((Bitboard)(1<<bEnd) & valid_moves)) {
        uncheckedMove(color, piece, bStart,bEnd);
        return true;
    }
    else return false;
}

void MoveGenerator::uncheckedMove(bool player, short piece, uint8_t start, uint8_t end) {
    chessBoard[0].pieces[player][piece] = chessBoard[0].pieces[player][piece] & (~(Bitboard)1<<start) | ((Bitboard)1<<end);
    chessBoard[0].AllPieces = (chessBoard[0].AllPieces & (~(Bitboard)1<<start)) | ((Bitboard)1<<end);
    chessBoard[0].AllBlackPieces = (chessBoard[0].AllBlackPieces & (~(Bitboard)1<<start)) | ((Bitboard)1<<end);
    chessBoard[0].AllWhitePieces = (chessBoard[0].AllWhitePieces & (~(Bitboard)1<<start)) | ((Bitboard)1<<end);
}
