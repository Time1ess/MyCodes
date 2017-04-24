// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-24 16:37
// Last modified: 2017-04-24 16:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    int arrangeCoins(int n) {
        int k = 0;
        while(n > k)
            n -= ++k;
        return k;
    }
};
