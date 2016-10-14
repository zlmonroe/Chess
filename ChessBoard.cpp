#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include <ctype.h>

short ChessBoard::getRowFromChar(char letter) {
    short val = (short)tolower(letter)-(short)'a';
    return val<9 ? val:-1;
}

bool ChessBoard::queryPiece(char column,short row, Bitboard board) {
    short file = getRowFromChar(column);
    if (file==-1) {
        board = board&0;
    }
    else {
        board=board&COLUMNMASK[file]&ROWMASK[row];
    }
    //returns true if population count of board is one
    return  (board != 0 && (board & (board-1)) == 0);
}

void ChessBoard::setupBoard() {
    WhitePieces[0] = PAWNSTART&ALLWHITESTART;
    WhitePieces[1] = ROOKSTART&ALLWHITESTART;
    WhitePieces[2] = KNIGHTSTART&ALLWHITESTART;
    WhitePieces[3] = BISHOPSTART&ALLWHITESTART;
    WhitePieces[4] = QUEENSTART&ALLWHITESTART;
    WhitePieces[5] = KINGSTART&ALLWHITESTART;

    BlackPieces[0] = PAWNSTART&ALLBLACKSTART;
    BlackPieces[1] = ROOKSTART&ALLBLACKSTART;
    BlackPieces[2] = KNIGHTSTART&ALLBLACKSTART;
    BlackPieces[3] = BISHOPSTART&ALLBLACKSTART;
    BlackPieces[4] = QUEENSTART&ALLBLACKSTART;
    BlackPieces[5] = KINGSTART&ALLBLACKSTART;

    AllWhitePieces = ALLWHITESTART;
    AllBlackPieces = ALLBLACKSTART;
    AllPieces = ALLWHITESTART|ALLBLACKSTART;
}

char* ChessBoard::userInput() {
    char c1,c2;
    do {
        std::cin >> c1;
        std::cin >> c2;
        std::cin.clear();
        std::cin.ignore();
        c1 = tolower(c1);
    }
    while (c2>'8' || c1>'i' || c2<'0' || c1<'a');
    char *s = new char[2]{c1,c2};
    return s;
}

short ChessBoard::findBoard(bool white, char* pos) {
    short column = getRowFromChar(pos[0]);
    short row = (int)pos[1]-(int)'1';
    if (white) {
        for (short i=0; i<6; i++) {
            if (WhitePieces[i]&COLUMNMASK[column]&ROWMASK[row]) {
                    std::cout << PIECES[i] << " found at " << pos[0] << pos[1] << "\n";
                    return i;
            }
        }
        return -1;
    }
    else {
        for (short i=0; i<6; i++) {
            if (BlackPieces[i]&COLUMNMASK[column]&ROWMASK[row]) {
                    std::cout << PIECES[i] << " found at " << pos[0] << pos[1] << "\n";
                    return i;
            }
        }
        return -1;
    }
}
std::bitset<64> ChessBoard::printableBitboard(Bitboard board) {
    std::bitset<64> x(board);
    return x;
}

Bitboard ChessBoard::valid(Bitboard loc, short piece, bool white) {
    Bitboard movement;
    if (piece==0 && white) {
        if (ROWMASK[1] && loc) {
            std::cout << "Pawn located on second row (2 move options)\n";
            //move 1 or 2 forward
            movement = ((loc << 8) | (loc << 16));
            std::cout << printableBitboard(movement) << std::endl;
        }
        else {
            //move 1 forward
            std::cout << "Pawn located on first row (1 move option)\n";
            movement = (loc << 8) & !AllPieces;
        }

        return movement;
    }
    else {
        return BLANK;
    }
}
