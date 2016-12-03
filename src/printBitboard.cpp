#include "printBitboard.h"
#include <iostream>
#include <windows.h>

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
	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

    WORD colors[] = {0x0F, 0xF0};

    std::cout << "Current Board:\n";
    std::string board[64];
    for (int i=0; i<64; i++) {
        if      ((chessBoard.pieces[0][0] >> i) & 0b1) board[i]=" P ";
        else if ((chessBoard.pieces[0][1] >> i) & 0b1) board[i]=" R ";
        else if ((chessBoard.pieces[0][2] >> i) & 0b1) board[i]=" N ";
        else if ((chessBoard.pieces[0][3] >> i) & 0b1) board[i]=" B ";
        else if ((chessBoard.pieces[0][4] >> i) & 0b1) board[i]=" Q ";
        else if ((chessBoard.pieces[0][5] >> i) & 0b1) board[i]=" K ";

        else if ((chessBoard.pieces[1][0] >> i) & 0b1) board[i]=" p ";
        else if ((chessBoard.pieces[1][1] >> i) & 0b1) board[i]=" r ";
        else if ((chessBoard.pieces[1][2] >> i) & 0b1) board[i]=" n ";
        else if ((chessBoard.pieces[1][3] >> i) & 0b1) board[i]=" b ";
        else if ((chessBoard.pieces[1][4] >> i) & 0b1) board[i]=" q ";
        else if ((chessBoard.pieces[1][5] >> i) & 0b1) board[i]=" k ";
        else board[i]="   ";
    }
    SetConsoleTextAttribute( hstdout, 0x6F);
    std::cout << "\n|  A  B  C  D  E  F  G  H  |\n|8";
    for (int row = 7; row>=0; row--) {
        for (int col = 0; col<8; col++) {
            short index = row*8+col;
            SetConsoleTextAttribute( hstdout, colors[(index+row%2)%2] );
            std::cout << board[index];
            SetConsoleTextAttribute( hstdout, csbi.wAttributes );
            if ((index+1)%8==0 && index+1!=8) {
                SetConsoleTextAttribute( hstdout, 0x6F);
                std::cout << row+1 <<"|\n" << "|" << row;
            }
            else if (index+1!=8) std::cout << "";
        }
    }
    SetConsoleTextAttribute( hstdout, 0x6F);
    std::cout << "1|\n|  A  B  C  D  E  F  G  H  |\n";

    FlushConsoleInputBuffer( hstdin );

	// Keep users happy
	SetConsoleTextAttribute( hstdout, csbi.wAttributes );
}
