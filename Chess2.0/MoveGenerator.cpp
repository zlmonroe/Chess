//
// Created by jon on 10/31/2016.
//

#include "MoveGenerator.h"
#include "magics.h"
#include "ChessConstBitboards.h"
#include "Chessboard.h"
#include <bitset>
#include "printBitboard.h"


Bitboard MoveGenerator::getBishopMoves(unsigned short pos, bool isBlack) {
    Bitboard index = ((chessBoard[0].AllPieces & BOccupancy[pos]) * BMagic[pos]) >> (64-BBits[pos]);
    std::cout << "Bishop array " << bArray;
    return slides[1][pos][index] & ~(isBlack? AllBlackPieces : AllWhitePieces);
}

Bitboard MoveGenerator::getRookMoves(unsigned short pos, bool isBlack) {
    Bitboard index = ((chessBoard[0].AllPieces & ROccupancy[pos]) * RMagic[pos]) >> (64-RBits[pos]);
    return slides[0][pos][bArray] & ~(isBlack? AllBlackPieces : AllWhitePieces);
}

Bitboard MoveGenerator::getKnightMoves(unsigned short position, bool isBlack) {
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

Bitboard MoveGenerator::getKingMoves(unsigned short position, bool isBlack) {
    return 0;
}

Bitboard MoveGenerator::getPawnMoves(unsigned short position, bool isBlack) {
    Bitboard pos = ((Bitboard)1<<(int)position);
    if (DEBUG) {
        std::cout<<"Found pawn at this position:\n";
        printBitboard((Bitboard)1<<(int)position);
    }
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
                pawn_one_forward = ((pos >> 8) & (~chessBoard[0].AllPieces));
                pawn_two_forward = (((((pos & ROWMASK[6]) >> 8) & ~chessBoard[0].AllPieces)>>8) & ~chessBoard[0].AllPieces);
                std::cout << "pawn two forward for black moves\n";
                printBitboard(((((pos & ROWMASK[6]) >> 8) & ~chessBoard[0].AllPieces)>>8) & ~chessBoard[0].AllPieces);
    }
    all_moves_possible = (left_attack | right_attack | pawn_one_forward | pawn_two_forward);
    return all_moves_possible;
}




Bitboard MoveGenerator::getQueenMoves(unsigned short position, bool isBlack) {
    return getRookMoves(position, isBlack) | getBishopMoves(position, isBlack);
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
    std::cout <<"Your choice\n";
    printBitboard((Bitboard)1<<bEnd);
    std::cout <<"Valid moves:\n";
    printBitboard(valid_moves);
    std::cout<<"Your choice and valid moves:\n";
    printBitboard((Bitboard)1<<bEnd & valid_moves);
    if ((Bitboard)1<<bEnd & valid_moves) {
        uncheckedMove(color, piece, bStart,bEnd);
        return true;
    }
    else {
        if (DEBUG) {
            std::cout << "The valid moves are: \n";
            printBitboard(valid_moves);
            std::cout << "\n";
        }
        return false;
    }
}

void MoveGenerator::uncheckedMove(bool player, short piece, unsigned short start, unsigned short end) {
    short whitePiece = chessBoard[0].findBoard(1,(Bitboard)1<<end);
    short blackPiece = chessBoard[0].findBoard(0,(Bitboard)1<<end);
    std::cout << whitePiece << " " << blackPiece;
    if (whitePiece>-1) chessBoard[0].pieces[0][whitePiece]-=((Bitboard)1<<end);
    else if (blackPiece>-1) chessBoard[0].pieces[1][blackPiece]-=((Bitboard)1<<end);

    chessBoard[0].pieces[player][piece] = chessBoard[0].pieces[player][piece] - ((Bitboard)1<<start) + ((Bitboard)1<<end);
    chessBoard[0].AllPieces = (chessBoard[0].AllPieces - ((Bitboard)1<<start)) + ((Bitboard)1<<end);
    chessBoard[0].AllBlackPieces = (chessBoard[0].AllBlackPieces - ((Bitboard)1<<start)) + ((Bitboard)1<<end);
    chessBoard[0].AllWhitePieces = (chessBoard[0].AllWhitePieces - ((Bitboard)1<<start)) + ((Bitboard)1<<end);
}
