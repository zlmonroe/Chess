//
// Created by jon on 11/25/2016.
//


#include <iostream>
#include "magics.h"
#include <ctype.h>
#include <fstream>

const int BitTable[64] = {
        63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
        51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
        26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
        58, 20, 37, 17, 36, 8
};

int pop_1st_bit(uint64_t *bb) {
    uint64_t b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

uint64_t rmask(int sq) {
    uint64_t result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r = rk+1; r <= 6; r++) result |= (1ULL << (fl + r*8));
    for(r = rk-1; r >= 1; r--) result |= (1ULL << (fl + r*8));
    for(f = fl+1; f <= 6; f++) result |= (1ULL << (f + rk*8));
    for(f = fl-1; f >= 1; f--) result |= (1ULL << (f + rk*8));
    return result;
}

uint64_t bmask(int sq) {
    uint64_t result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r=rk+1, f=fl+1; r<=6 && f<=6; r++, f++) result |= (1ULL << (f + r*8));
    for(r=rk+1, f=fl-1; r<=6 && f>=1; r++, f--) result |= (1ULL << (f + r*8));
    for(r=rk-1, f=fl+1; r>=1 && f<=6; r--, f++) result |= (1ULL << (f + r*8));
    for(r=rk-1, f=fl-1; r>=1 && f>=1; r--, f--) result |= (1ULL << (f + r*8));
    return result;
}

uint64_t ratt(int sq, uint64_t block) {
    uint64_t result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r = rk+1; r <= 7; r++) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }
    for(r = rk-1; r >= 0; r--) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }
    for(f = fl+1; f <= 7; f++) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }
    for(f = fl-1; f >= 0; f--) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }
    return result;
}

uint64_t batt(int sq, uint64_t block) {
    uint64_t result = 0ULL;
    int rk = sq/8, fl = sq%8, r, f;
    for(r = rk+1, f = fl+1; r <= 7 && f <= 7; r++, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk+1, f = fl-1; r <= 7 && f >= 0; r++, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl+1; r >= 0 && f <= 7; r--, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    for(r = rk-1, f = fl-1; r >= 0 && f >= 0; r--, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }
    return result;
}

int count_1s(uint64_t b) {
    int r;
    for(r = 0; b; r++, b &= b - 1);
    return r;
}

uint64_t index_to_uint64(int index, int bits, uint64_t m) {
    int i, j;
    uint64_t result = 0ULL;
    for(i = 0; i < bits; i++) {
        j = pop_1st_bit(&m);
        if(index & (1 << i)) result |= (1ULL << j);
    }
    return result;
}

int main() {



    static Bitboard slides[2][64][4096];



    for (int bishop = 0; bishop < 2; bishop++) {

        for (int sq = 0; sq < 64; sq++) {

            uint64_t b[4096], a[4096], used[4096];
            Bitboard mask = bishop ? bmask(sq) : rmask(sq);
            int n = count_1s(mask);
            int max = 0;
            int i;
            for (i = 0; i < 4096; i++) {
                slides[bishop][sq][i] = 0ULL;
            }
            for (i = 0; i < (1 << n); i++) {
                b[i] = index_to_uint64(i, n, mask);             // blocks
                a[i] = bishop ? batt(sq, b[i]) : ratt(sq, b[i]); // attacks

                uint64_t index = !bishop ? ((b[i] & ROccupancy[sq]) * RMagic[sq]) >> (64 - RBits[sq]) : ((b[i] & BOccupancy[sq]) * BMagic[sq]) >> (64 - BBits[sq]);

                slides[bishop][sq][index] = a[i];

            }
        }
    }

    std::ofstream database;
    database.open ("slidingMoves.txt");
    database << "static const Bitboard slides[2][64][4096] = {\n";
    for (int bishop = 0; bishop < 2; bishop++) {
        database << "{";
        for (int sq = 0; sq < 64; sq++) {
            database << "{";
            for (int index = 0; index < 4096; index++) {
                database << slides[bishop][sq][index] << "ULL,";
            }
            database << "},\n";
        }
        database << "},\n";
    }


    database << "};";
    database.close();

   /* Bitboard test[2][2][2] = {
            {{0,1},
                    {2,3}},

            {{4,5},{6,7}}
    };*/

}
