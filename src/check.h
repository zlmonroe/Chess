#pragma once
#include "MoveGenerator.h"

class Check {
public:
    Check(MoveGenerator m);
    bool check(bool color);//takes in the color of the defending player and returns true if their king is in check
    private:
        MoveGenerator moves;//returns a bitboard with all the possible attacking moves    -
   };
