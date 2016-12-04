//
// Created by jon on 10/31/2016.
//

#include "MoveGenerator.h"
#include "magics.h"
#include "ChessConstBitboards.h"
#include "ChessBoard.h"
//#include <bitset>
#include "printBitboard.h"


Bitboard MoveGenerator::getBishopMoves(unsigned short pos, bool isBlack, ChessBoard* cb) {
    Bitboard index = ((cb[0].AllPieces & BOccupancy[pos]) * BMagic[pos]) >> (64-BBits[pos]);
    return bishopMoves[pos][index] & ~(isBlack? cb[0].AllBlackPieces : cb[0].AllWhitePieces);
}

Bitboard MoveGenerator::getRookMoves(unsigned short pos, bool isBlack, ChessBoard* cb) {
    Bitboard index = ((cb[0].AllPieces & ROccupancy[pos]) * RMagic[pos]) >> (64-RBits[pos]);
    return rookMoves[pos][index] & ~(isBlack? cb[0].AllBlackPieces : cb[0].AllWhitePieces);
}

Bitboard MoveGenerator::getKnightMoves(unsigned short position, bool isBlack, ChessBoard* cb) {
    Bitboard start = (Bitboard)1<<position;
    Bitboard clearA = COLUMNCLEAR[0];
    Bitboard clearAB = COLUMNCLEAR[0]&COLUMNCLEAR[1];
    Bitboard clearH = COLUMNCLEAR[7];
    Bitboard clearGH = COLUMNCLEAR[6]&COLUMNCLEAR[7];
    Bitboard own;
    if (isBlack)
        own = cb[0].AllBlackPieces; //Switch to allBlackPieces when implemented
    else
        own = cb[0].AllWhitePieces; //Switch to allWhitePieces when implemented

    return ((((start&clearA)<<15)|((start&clearAB)<<6)|((start&clearAB)>>10)|((start&clearA)>>17)|((start&clearH)>>15)|((start&clearGH)>>6)|((start&clearGH)<<10)|(start&clearH)<<17)&~own);
}

Bitboard MoveGenerator::getKingMoves(unsigned short position, bool isBlack, ChessBoard* cb) {
    Bitboard left_attack;
    Bitboard right_attack;
    Bitboard forward_attack;
    Bitboard backward_attack;
    Bitboard left_forward_diagonal_attack;
    Bitboard right_forward_diagonal_attack;
    Bitboard left_backward_diagonal_attack;
    Bitboard right_backward_diagonal_attack;
    Bitboard all_moves_possible;

    left_attack = ((COLUMNCLEAR[0] & (cb[0].pieces[isBlack][5]) >> 1));
    right_attack = ((COLUMNCLEAR[7] & (cb[0].pieces[isBlack][5]) << 1));
    forward_attack = (cb[0].pieces[isBlack][5] << 8);
    backward_attack = (cb[0].pieces[isBlack][5] >> 8);
    left_forward_diagonal_attack = ((COLUMNCLEAR[0] & (cb[0].pieces[isBlack][5]) << 7));
    right_forward_diagonal_attack = ((COLUMNCLEAR[7] & (cb[0].pieces[isBlack][5]) << 9));
    left_backward_diagonal_attack = ((COLUMNCLEAR[0] & (cb[0].pieces[isBlack][5]) >> 9));
    right_backward_diagonal_attack = ((COLUMNCLEAR[7] & (cb[0].pieces[isBlack][5]) >> 7));
    all_moves_possible = (left_attack | right_attack | forward_attack | backward_attack | left_forward_diagonal_attack | right_forward_diagonal_attack | left_backward_diagonal_attack | right_backward_diagonal_attack);
    return all_moves_possible & ~(isBlack ? cb[0].AllBlackPieces : chessBoard[1].AllWhitePieces);
}

Bitboard MoveGenerator::getPawnMoves(unsigned short position, bool isBlack, ChessBoard* cb) {
    Bitboard pos = ((Bitboard)1<<(int)position);
#if DEBUG
    std::cout<<"Found pawn at this position:\n";
    printBitboard((Bitboard)1<<(int)position);
#endif
    Bitboard left_attack;
    Bitboard right_attack;
    Bitboard pawn_one_forward;
    Bitboard pawn_two_forward;
    Bitboard all_moves_possible;

    if (!isBlack) {
                left_attack = ((COLUMNCLEAR[0] & pos) << 7) & (cb[0].AllBlackPieces | cb[0].Enpessant[0]);
                right_attack = ((COLUMNCLEAR[7] & pos) << 9) & (cb[0].AllBlackPieces | cb[0].Enpessant[0]);
                pawn_one_forward = ((pos << 8) & ~(cb[0].AllPieces));
                pawn_two_forward = (((((pos & ROWMASK[1]) << 8) & ~cb[0].AllPieces)<<8) & ~cb[0].AllPieces);
    }
    else {
                left_attack = ((COLUMNCLEAR[0] & pos) >> 9) & (cb[0].AllWhitePieces | cb[0].Enpessant[1]);
                right_attack = ((COLUMNCLEAR[7] & pos) >> 7) & (cb[0].AllWhitePieces | cb[0].Enpessant[1]);
                pawn_one_forward = ((pos >> 8) & (~cb[0].AllPieces));
                pawn_two_forward = (((((pos & ROWMASK[6]) >> 8) & ~cb[0].AllPieces)>>8) & ~cb[0].AllPieces);
    }
    all_moves_possible = (left_attack | right_attack | pawn_one_forward | pawn_two_forward);
    return all_moves_possible;
}




Bitboard MoveGenerator::getQueenMoves(unsigned short position, bool isBlack, ChessBoard* cb) {
    return getRookMoves(position, isBlack, cb) | getBishopMoves(position, isBlack, cb);
}


bool MoveGenerator::isValidMove(unsigned short userMove) {

    Bitboard valid_moves;
    unsigned short bStart = (userMove & 0b0000111111000000)>>6;
    unsigned short bEnd = (userMove & 0b111111);
    unsigned short otherStuff = (userMove & 0b0111000000000000) >>12;
    bool color = (userMove & 0b1000000000000000)>>15;
    short piece = chessBoard[0].findBoard(color, (Bitboard)1<<bStart);

    if (piece>=0) std::cout << "Found " << PIECE_NAMES[piece] << "\n";
    else {std::cout << "No piece found" << std::endl;}

    switch (piece) {

        case 0:
            valid_moves = getPawnMoves(bStart, color, chessBoard);
            break;

        case 1:
            valid_moves = getRookMoves(bStart, color, chessBoard);
            break;

        case 2:

            valid_moves = getKnightMoves(bStart, color, chessBoard);
            break;

        case 3:

            valid_moves = getBishopMoves(bStart, color, chessBoard);
            break;

        case 4:

            valid_moves = getQueenMoves(bStart, color, chessBoard);
            break;

        case 5:

            valid_moves = getKingMoves(bStart, color, chessBoard);
            break;

        default:

            std::cout<<"No piece found at that spot!"<<std::endl;
            valid_moves = (Bitboard)0x0000;

    }
#if DEBUG
    std::cout <<"Your choice\n";
    printBitboard((Bitboard)1<<bEnd);
    std::cout <<"Valid moves:\n";
    printBitboard(valid_moves);
    std::cout<<"Your choice and valid moves:\n";
    printBitboard((Bitboard)1<<bEnd & valid_moves);
#endif
    if ((Bitboard)1<<bEnd & valid_moves) {
        ChessBoard* testBoard = new ChessBoard(chessBoard[0]);
        uncheckedMove(color, piece, bStart, bEnd, testBoard);
        //Bitboard newKing = chessBoard[0].pieces[color][5];
        if(!check(color, testBoard)) {
            //chessBoard = testBoard;
            uncheckedMove(color, piece, bStart, bEnd, chessBoard);
            return true;
        } else {
            std::cout << "That move would put you into check";
            return false;
        }
    }
    else {
#if DEBUG
        std::cout << "The valid moves are: \n";
        printBitboard(valid_moves);
        std::cout << "\n";
#endif
        return false;
    }
}

void MoveGenerator::uncheckedMove(bool player, short piece, unsigned short start, unsigned short end, ChessBoard* cb) {

    cb[0].pieces[player][piece] = cb[0].pieces[player][piece] - ((Bitboard)1<<start) + ((Bitboard)1<<end);
    cb[0].AllPieces = cb[0].AllPieces - ((Bitboard)1<<start) + ((Bitboard)1<<end);
    short captureType = cb[0].findBoard(!player, (Bitboard)1<<end);
    if (captureType > -1) {
        cb[0].pieces[!player][captureType] -= ((Bitboard) 1 << end);
        std::cout << "You captured a " << PIECE_NAMES[captureType];
    }
    if (player) {   // black
        cb[0].AllWhitePieces -= cb[0].AllWhitePieces & ((Bitboard)1 << end);    // capture white
        cb[0].AllBlackPieces = (cb[0].AllBlackPieces - ((Bitboard)1 << start)) + ((Bitboard)1 << end);
    } else {        // white
        cb[0].AllBlackPieces -= cb[0].AllBlackPieces & ((Bitboard)1 << end);    // capture black
        cb[0].AllWhitePieces = (cb[0].AllWhitePieces - ((Bitboard)1 << start)) + ((Bitboard)1 << end);
    }
}


 Bitboard MoveGenerator::getAllMoves(bool color, ChessBoard* cb) {
 	Bitboard totalMoves = 0ULL;
 	int piece;
 	unsigned short loc;
 	for (loc = 0; loc < 64; loc++) {
 		piece = cb[0].findBoard(color, (Bitboard)1<<loc);
 		if (piece >= 0) {
#if DEBUG
            std::cout << "\nGUY's IT'S HERE!!!! " << PIECE_NAMES[piece] << "\n";
#endif
 			switch (piece) {
 			case 0:
 				totalMoves |= getPawnMoves(loc, color, cb);
 				break;
 			case 1:
 				totalMoves |= getRookMoves(loc, color, cb);
 				break;
 			case 2:
 				totalMoves |= getKnightMoves(loc, color, cb);
 				break;
 			case 3:
 				totalMoves |= getBishopMoves(loc, color, cb);
 				break;
 			case 4:
 				totalMoves |= getQueenMoves(loc, color, cb);
  				break;
  			case 5:
  				totalMoves |= getKingMoves(loc, color, cb);
  			}
  		}
  	}
#if DEBUG
     std::cout << "\nGUY's THE BITBOARD IS HERE\n";
     printBitboard(totalMoves);
#endif
 	return totalMoves;
 }
