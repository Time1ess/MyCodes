// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 10:00
// Last modified: 2017-06-27 10:00
// Filename: solution.cpp
// Description:
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        unsigned int l = 1, r = n+1, m, g;
        while(l < r)
        {
            m = l + (r - l) / 2;
            g = guess(m);
            if(g == 0)
                return m;
            else if(g == -1)
                r = m;
            else
                l = m+1;
        }
        return l;
    }
};
