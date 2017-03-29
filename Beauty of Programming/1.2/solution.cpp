// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 11:08
// Last modified: 2017-03-29 11:20
// Filename: solution.cpp
// Description:
#include <cstdio>

#define HALF_BITS_LENGTH 4
#define FULL_MASK 255
#define LMASK (FULL_MASK << HALF_BITS_LENGTH)
#define RMASK (FULL_MASK >> HALF_BITS_LENGTH)
#define RSET(b, n) (b = (b & LMASK) | (n))
#define LSET(b, n) (b = (b & RMASK) | (n << HALF_BITS_LENGTH))
#define RGET(b) (b & RMASK)
#define LGET(b) ((b & LMASK) >> HALF_BITS_LENGTH)
#define GRIDW 3

int main()
{
    unsigned char b;
    for(LSET(b, 1); LGET(b) <= GRIDW * GRIDW; LSET(b, LGET(b)+1))
        for(RSET(b, 1); RGET(b) <= GRIDW * GRIDW; RSET(b, RGET(b)+1))
            if(LGET(b) % GRIDW != RGET(b) % GRIDW)
                printf("A = %d, B = %d\n", LGET(b), RGET(b));
    return 0;
}
