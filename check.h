#pragma once

class Check {
public:
	bool check(bool color);//takes in the color of the defending player and returns true if their king is in check
private:
	Bitboard getAllMoves(bool color);//returns a bitboard with all the possible attacking moves
	Bitboard getKingPos(bool color);//returns a bitboard with the defending king's position
	
};
