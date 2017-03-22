// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-22 11:31
// Last modified: 2017-03-22 11:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && (1162261467 % n == 0);
    }
};
