#include "player.h"
#include "ChessBoard.h"
#include "MoveGenerator.h"
#include "printBitboard.h"
int main() {
    ChessPlayer whitePlayer = ChessPlayer(0);
    ChessPlayer blackPlayer = ChessPlayer(1);
    ChessPlayer players[2] = {whitePlayer, blackPlayer};

    ChessBoard chessBoard;
    chessBoard.setupBoard();

    MoveGenerator moveGen = MoveGenerator(&chessBoard);

    printChessBoard(chessBoard);

    bool checkmate=0, stalemate=0, player=0;
    while (!(checkmate | stalemate)){
        std::cout << (!player ? "White's turn\n":"Black's turn\n");

        if (moveGen.check(player, &chessBoard)) {
            if (moveGen.checkmate(player, &chessBoard)) {
                std::cout << (player ? "Black" : "White") << " in in checkmate. " << (!player ? "Black" : "White") << " wins!\n";
                checkmate = true;
                break;
            } else {
                std::cout << (player ? "Black" : "White") << " is currently in check\n";
            }

        }
        bool valid;
        unsigned short userMove;
        do {


            userMove = players[player].getConvertInput();

            valid = moveGen.isValidMove(userMove);
            std::cout << "That move is ";
            std::cout << (valid ? "valid\n":"not valid\n");
        } while (!valid);

        printChessBoard(chessBoard);

        player=!player;
    }
    std::cout << "Press any key to exit";
    std::getchar();
}
