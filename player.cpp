// ChessPlayer.cpp : Defines the entry point for the console application.
//

#include "player.h"
#include <iostream>
#include <string>
#include <bitset>

int main()
{
	ChessPlayer p = ChessPlayer(0);
	std::cout << std::bitset<16>(p.getConvertInput());
	return 0;
}
ChessPlayer::ChessPlayer(unsigned short c) {
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

	std::cout << "Enter your move";
	std::getline(std::cin, input);

	startC = ((int)input[0]-65);
	startR = ((int)input[1]-49);
	stPos = startR * 8 + startC;

	endC = ((int)input[2] - 65);
	endR = ((int)input[3] - 49);
	enPos = endR * 8 + endC;

	special = input[4];

	switch (special) {
	case 'n':
		spInt = 0;
		break;
	case 'r':
		spInt = 0b110;
		break;
	case 'l':
		spInt = 0b101;
		break;
	case 'q':
		spInt = 0b100;
		break;
	case 'c':
		spInt = 0b001;
		break;
	case 'b':
		spInt = 0b011;
		break;
	case 'k':
		spInt = 0b010;
		break;
	}
	move = (color<<1) + (spInt << 3) + (stPos<<6) + (enPos);
	return move;
}
