// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-01-16 21:37
// Last modified: 2017-01-16 21:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    int hammingDistance(int x, int y) {
        int cnt = 0;
        int k = x^y;
        while(k)
        {
            cnt++;
            k &= (k-1);
        }
        return cnt;
    }
};
