// ChessPlayer.cpp : Defines the entry point for the console application.
//
#include "player.h"
#include "ChessConstBitboards.h"
#include <bitset>

ChessPlayer::ChessPlayer(bool c) {
	color = c;
}
unsigned short ChessPlayer::getConvertInput() {
	short startC;
	short startR;
	short stPos;

	short endC;
	short endR;
	short enPos;

	char special;
	short spInt;
	std::string input;

	std::cout << "Enter your move:\n";
	//std::getline(std::cin, input);
    std::cin >> input;

	startC = ((int)toupper(input[0])-65);
	startR = ((int)input[1]-49);
	stPos = startR * 8 + startC;

	endC = ((int)toupper(input[2]) - 65);
	endR = ((int)input[3] - 49);
	enPos = endR * 8 + endC;

	if (input.length() < 5) {
		spInt = 0b000;
	}
	else {
		special = toupper(input[4]);
		switch (special) {
		case 'R':
			spInt = 0b110;
			break;
		case 'L':
			spInt = 0b101;
			break;
		case 'Q':
			spInt = 0b100;
			break;
		case 'C':
			spInt = 0b001;
			break;
		case 'B':
			spInt = 0b011;
			break;
		case 'K':
			spInt = 0b010;
			break;
		}
	}

	unsigned short move = (color<<15) | (spInt << 12) | (stPos<<6) | (enPos);
#if DEBUG
	std::cout << "start: " << stPos << " end: " << enPos << "\n";
#endif
	return move;
}
