#include "ChessBoard.h"
#include "ChessConstBitboards.h"
#include <ctype.h>

short ChessBoard::getRowFromChar(char letter) {
    short val = (short)tolower(letter)-(short)'a';
    return val<9 ? val:(short)-1;
}

bool ChessBoard::queryPiece(char column,short row, Bitboard board) {
    short file = getRowFromChar(column);
    if (file==-1) {
        board = board & 0;
    }
    else {
        board=board & COLUMNMASK[file] & ROWMASK[row];
    }
    //returns true if population count of board is one
    return  (board != 0 && (board & (board-1)) == 0);
}

void ChessBoard::setupBoard() {

    pieces[0][0] = PAWNSTART & ALLWHITESTART;
    pieces[0][1] = ROOKSTART & ALLWHITESTART;
    pieces[0][2] = KNIGHTSTART & ALLWHITESTART;
    pieces[0][3] = BISHOPSTART & ALLWHITESTART;
    pieces[0][4] = QUEENSTART & ALLWHITESTART;
    pieces[0][5] = KINGSTART & ALLWHITESTART;

    pieces[1][0] = PAWNSTART & ALLBLACKSTART;
    pieces[1][1] = ROOKSTART & ALLBLACKSTART;
    pieces[1][2] = KNIGHTSTART & ALLBLACKSTART;
    pieces[1][3] = BISHOPSTART & ALLBLACKSTART;
    pieces[1][4] = QUEENSTART & ALLBLACKSTART;
    pieces[1][5] = KINGSTART & ALLBLACKSTART;

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
        c1 = (char)tolower(c1);
    }
    while (c2>'8' || c1>'i' || c2<'0' || c1<'a');
    char *s = new char[2]{c1,c2};
    return s;
}

/**
 * Determines which
 * @param white
 * @param pos
 * @return
 */
uint8_t ChessBoard::findBoard(bool white, char* pos) {
    Bitboard loc = (Bitboard)1 << ((pos[0] - 'a') + (pos[1] - '1')*8);
    uint8_t i;
    for (i=5; i>=0; i--) {
        if (pieces[!white][i] & loc) {
            std::cout << PIECES[i] << " found at " << pos[0] << pos[1] << "\n";
            break;
        }
    }
    return i;
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
