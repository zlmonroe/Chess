#ifndef VALID_H_INCLUDED
#define VALID_H_INCLUDED

class MoveValidator{
private:

    bool isValidMove(unsnigned short userMove);
    Bitboard getPawnMoves(color, bStart);
    Bitboard getRookMoves(color, bStart);
    Bitboard getKnightMoves(color, bStart);
    Bitboard getBishopMoves(color, bStart);
    Bitboard getQueenMoves(color, bStart);
    Bitboard getKingMoves(color, bStart);

};

#endif // VALID_H_INCLUDED
