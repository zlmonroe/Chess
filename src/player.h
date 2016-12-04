#pragma once
#include <string>
//#include <unordered_map>
class ChessPlayer {
public:
	ChessPlayer(bool c);
	unsigned short getConvertInput();
private:
	unsigned short move; //converted input
	unsigned short color; //users color
};
