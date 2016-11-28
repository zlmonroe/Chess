#ifndef PRINTBOARD_H
#define PRINTBOARD_H
#include "ChessConstBitboards.h"

void printBitboard(const Bitboard bitboard) {
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col <= 7; ++col) {
            if (bitboard & (1ULL << ((row * 8) + col))) {
                std::cout << "1 ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout  << std::endl;
}

void  printChessBoard(ChessBoard chessBoard) {
    std::cout << "Current Board:\n";
    std::string board[64];
    for (int i=0; i<64; i++) {
        if      ((chessBoard.pieces[0][0] >> i) & 0b1) board[i]="WP";
        else if ((chessBoard.pieces[0][1] >> i) & 0b1) board[i]="WR";
        else if ((chessBoard.pieces[0][2] >> i) & 0b1) board[i]="WN";
        else if ((chessBoard.pieces[0][3] >> i) & 0b1) board[i]="WB";
        else if ((chessBoard.pieces[0][4] >> i) & 0b1) board[i]="WQ";
        else if ((chessBoard.pieces[0][5] >> i) & 0b1) board[i]="WK";

        else if ((chessBoard.pieces[1][0] >> i) & 0b1) board[i]="BP";
        else if ((chessBoard.pieces[1][1] >> i) & 0b1) board[i]="BR";
        else if ((chessBoard.pieces[1][2] >> i) & 0b1) board[i]="BN";
        else if ((chessBoard.pieces[1][3] >> i) & 0b1) board[i]="BB";
        else if ((chessBoard.pieces[1][4] >> i) & 0b1) board[i]="BQ";
        else if ((chessBoard.pieces[1][5] >> i) & 0b1) board[i]="BK";
        else board[i]="XX";
    }
    std::cout << "     A  B  C  D  E  F  G  H\n     -----------------------\n8   |";
    for (int row = 7; row>=0; row--) {
        for (int col = 0; col<8; col++) {
            short index = row*8+col;
            std::cout << board[index];
            if ((index+1)%8==0 && index+1!=8)
                std::cout << "|   " << row+1 <<" \n" << row << "   |";
            else if (index+1!=8) std::cout << " ";
        }
    }
    std::cout << "|   1\n     -----------------------\n     A  B  C  D  E  F  G  H\n";
}
#endif // PRINTBOARD_H
