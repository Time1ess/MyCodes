// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-15 16:34
// Last modified: 2017-05-15 16:34
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0 || (x != 0 && x % 10 == 0))
            return false;
        int y = 0;
        while(y < x)
        {
            y = y * 10 + x % 10;
            x /= 10;
        }
        return (x == y) || (x == y / 10);
    }
};
