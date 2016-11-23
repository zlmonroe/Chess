#include <iostream>
#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include "valid.h"

Bitboard MoveValidator::getPawnMoves(short color, Bitboard bStart) {

    Bitboard left_attack;
    Bitboard right_attack;
    Bitboard pawn_one_forward;
    Bitboard pawn_two_forward;
    Bitboard all_moves_possible;

    if ~(color) {

            left_attack = ((COLUMNCLEAR[0] & ChessBoard::WhitePieces[0]) << 7) & (ChessBoard::AllBlackPieces | ChessBoard::Enpessant);

            right_attack = ((COLUMNCLEAR[7] & ChessBoard::WhitePieces[0]) << 9) & (ChessBoard::AllBlackPieces | ChessBoard::Enpessant);

            pawn_one_forward = ((ChessBoard::WhitePieces[0] << 8) & ~(ChessBoard::AllPieces));

            pawn_two_forward = ((((ChessBoard::WhitePieces[0] & ROWMASK[2]) << 8) & ~(ChessBoard::AllPieces) << 8) & ~(ChessBoard::AllPieces));

    } else {

            left_attack = ((COLUMNCLEAR[0] & ChessBoard::BlackPieces[0]) >> 9) & (ChessBoard::AllWhitePieces | ChessBoard::Enpessant);

            right_attack = ((COLUMNCLEAR[7] & ChessBoard::BlackPieces[0]) >> 7) & (ChessBoard::AllWhitePieces | ChessBoard::Enpessant);

            pawn_one_forward = ((ChessBoard::BlackPieces[0] >> 8) & ~(ChessBoard::AllPieces);

            pawn_two_forward = ((((ChessBoard::BlackPieces[0] & ROWMASK[7]) >> 8) & ~(ChessBoard::AllPieces) >> 8) & ~(ChessBoard::AllPieces));

    }

    all_moves_possible = (left_attack | right_attack | pawn_one_forward | pawn_two_forward);

    return all_moves_possible;

}
