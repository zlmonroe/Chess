#pragma once

class Check {
public:
    Check(MoveGenerater m);
    bool check(bool color);//takes in the color of the defending player and returns true if their king is in check
    private:
        MoveGenerator moves;//returns a bitboard with all the possible attacking moves    -
   };
