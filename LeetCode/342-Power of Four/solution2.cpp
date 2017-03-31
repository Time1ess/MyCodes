// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-31 15:05
// Last modified: 2017-03-31 15:05
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool isPowerOfFour(int num) {
        // make sure num is positive and only has one bit sets to 1.
        return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0x55555555) == num);
    }
};
