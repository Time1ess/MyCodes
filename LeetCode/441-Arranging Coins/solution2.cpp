// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-24 16:42
// Last modified: 2017-04-24 16:42
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int arrangeCoins(int n) {
        return (sqrt(1 + 8 * (double)n) - 1) / 2;
    }
};
