#include "printBitboard.h"

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
        if      ((chessBoard.pieces[0][0] >> i) & 0b1) board[i]="P";
        else if ((chessBoard.pieces[0][1] >> i) & 0b1) board[i]="R";
        else if ((chessBoard.pieces[0][2] >> i) & 0b1) board[i]="N";
        else if ((chessBoard.pieces[0][3] >> i) & 0b1) board[i]="B";
        else if ((chessBoard.pieces[0][4] >> i) & 0b1) board[i]="Q";
        else if ((chessBoard.pieces[0][5] >> i) & 0b1) board[i]="K";

        else if ((chessBoard.pieces[1][0] >> i) & 0b1) board[i]="p";
        else if ((chessBoard.pieces[1][1] >> i) & 0b1) board[i]="r";
        else if ((chessBoard.pieces[1][2] >> i) & 0b1) board[i]="n";
        else if ((chessBoard.pieces[1][3] >> i) & 0b1) board[i]="b";
        else if ((chessBoard.pieces[1][4] >> i) & 0b1) board[i]="q";
        else if ((chessBoard.pieces[1][5] >> i) & 0b1) board[i]="k";
        else board[i]= (char)254;
    }
    std::cout << "    A B C D E F G H\n    ---------------\n8  |";
    for (int row = 7; row>=0; row--) {
        for (int col = 0; col<8; col++) {
            short index = row*8+col;
            std::cout << board[index];
            if ((index+1)%8==0 && index+1!=8)
                std::cout << "|  " << row+1 <<" \n" << row << "  |";
            else if (index+1!=8) std::cout << " ";
        }
    }
    std::cout << "|  1\n    ---------------\n    A B C D E F G H\n";
}
