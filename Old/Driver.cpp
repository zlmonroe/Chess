#include "ChessBoard.h"

int main() {
    ChessBoard cb = ChessBoard();
    cb.setupBoard();
    char* pieceStart;
    char* pieceEnd;
    short boardNum=-1;
    short rowS,columnS,rowE,columnE;

    do {
        std::cout << "Start:" << std::endl;
        pieceStart = cb.userInput();
        //std::cout << "End:" << std::endl;
        //pieceEnd = cb.userInput();

        // 0:pawn, 1:rook, 2:knight 3:bishop 4:queen 5:king
        boardNum = cb.findBoard(true, pieceStart);
    }
    while (boardNum==-1);
    columnS = (int)pieceStart[0]-(int)'a';
    rowS = (int)pieceStart[1]-(int)'1';
    cb.valid(ROWMASK[rowS]&COLUMNMASK[columnS],boardNum,true);
}
