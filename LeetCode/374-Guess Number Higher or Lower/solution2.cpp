// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 10:02
// Last modified: 2017-06-27 10:02
// Filename: solution2.cpp
// Description:
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        unsigned int l = 1, r = n+1, m1, m2, g1, g2;
        while(l < r)
        {
            m1 = l + (r - l) / 3;
            m2 = r - (r - l) / 3;
            g1 = guess(m1);
            g2 = guess(m2);
            if(g1 == 0)
                return m1;
            else if(g2 == 0)
                return m2;
            else if(g1 == -1)
                r = m1;
            else if(g2 == 1)
                l = m2 + 1;
            else
            {
                l = m1 + 1;
                r = m2;
            }
        }
        return l;
    }
};
