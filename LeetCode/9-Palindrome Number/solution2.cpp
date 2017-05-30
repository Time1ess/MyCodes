// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-15 16:39
// Last modified: 2017-05-15 16:39
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0)
            return false;
        int y = 0, z = x;
        while(z)
        {
            y = y * 10 + z % 10;
            z /= 10;
        }
        return x == y;
    }
};
