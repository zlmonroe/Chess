#pragma once

class Check {
public:
	bool check(bool aColor, bool dColor);
private:
	Bitboard getAllMoves(bool color);//returns a bitboard with all the possible attacking moves
	Bitboard getKingPos(bool color);//returns a bitboard with the defending king's position
	
};