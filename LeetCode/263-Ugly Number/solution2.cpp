// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 15:42
// Last modified: 2017-03-27 15:42
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool isUgly(int num) {
        if(num == 1)
            return true;
        else if(num == 0)
            return false;
        int n = num;
        while(n % 2 == 0)
            n >>= 1;
        while(n % 5 == 0)
            n /= 5;
        while(n % 3 == 0)
            n /= 3;
        return n == 1; 
    }
};
