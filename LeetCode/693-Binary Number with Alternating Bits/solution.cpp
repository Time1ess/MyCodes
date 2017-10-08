// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-08 15:30
// Last modified: 2017-10-08 15:30
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool hasAlternatingBits(int n) {
        char last = n & 1;
        n >>= 1;
        while(n)
        {
            if(!((n & 1) ^ last))
                return false;
            last = n & 1;
            n >>= 1;
        }
        return true;
    }
};
