// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 11:18
// Last modified: 2017-03-29 11:20
// Filename: solution2.cpp
// Description:
#include <cstdio>

struct {
    unsigned char a:4;
    unsigned char b:4;
}i;

int main()
{
    for(i.a = 1; i.a <= 9; i.a++)
        for(i.b = 1; i.b <= 9; i.b++)
            if(i.a % 3 != i.b % 3)
                printf("A = %d, b = %d\n", i.a, i.b);
    return 0;
}
