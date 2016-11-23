#include <iostream>
#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include "valid.h"

Bitboard MoveValidator::getKingMoves(short color, Bitboard bStart) {

    Bitboard left_attack;
    Bitboard right_attack;
    Bitboard forward_attack;
    Bitboard backward_attack;
    Bitboard left_forward_diagonal_attack;
    Bitboard right_forward_diagonal_attack;
    Bitboard left_backward_diagonal_attack;
    Bitboard right_backward_diagonal_attack;
    Bitboard all_moves_possible;

    if (~color) {

        left_attack = ((COLUMNCLEAR[0] & (ChessBoard::WhitePieces[5]) >> 1));

        right_attack = ((COLUMNCLEAR[7] & (ChessBoard::WhitePieces[5]) << 1));

        forward_attack = (ChessBoard::WhitePieces[5] << 8);

        backward_attack = (ChessBoard::WhitePieces[5] >> 8);

        left_forward_diagonal_attack = ((COLUMNCLEAR[0] & (ChessBoard::WhitePieces[5]) << 7));

        right_forward_diagonal_attack = ((COLUMNCLEAR[7] & (ChessBoard::WhitePieces[5]) << 9));

        left_backward_diagonal_attack = ((COLUMNCLEAR[0] & (ChessBoard::WhitePieces[5]) >> 9));

        right_backward_diagonal_attack = ((COLUMNCLEAR[7] & (ChessBoard::WhitePieces[5]) >> 7));

    } else {

        left_attack = ((COLUMNCLEAR[0] & (ChessBoard::BlackPieces[5]) << 1));

        right_attack = ((COLUMNCLEAR[7] & (ChessBoard::BlackPieces[5]) >> 1));

        forward_attack = (ChessBoard::BlackPieces[[5] >> 8);

        backward_attack = (ChessBoard::BlackPieces[[5] << 8);

        left_forward_diagonal_attack = ((COLUMNCLEAR[0] & (ChessBoard::BlackPieces[[5]) >> 7));

        right_forward_diagonal_attack = ((COLUMNCLEAR[7] & (ChessBoard::BlackPieces[[5]) >> 9));

        left_backward_diagonal_attack = ((COLUMNCLEAR[0] & (ChessBoard::BlackPieces[[5]) << 9));

        right_backward_diagonal_attack = ((COLUMNCLEAR[7] & (ChessBoard::BlackPieces[[5]) << 7));

    }

    all_moves_possible = (left_attack | right_attack | forward_attack | backward_attack | left_forward_diagonal_attack | right_forward_diagonal_attack | left_backward_diagonal_attack | right_backward_diagonal_attack);

    return all_moves_possible;

}
