// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 15:40
// Last modified: 2017-03-27 15:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isUgly(int num) {
        if(num == 1)
            return true;
        else if(num == 0)
            return false;
        int n = num;
        while(true)
        {
            if(n % 5 == 0)
                n /= 5;
            else if(n % 3 == 0)
                n /= 3;
            else if(n % 2 == 0)
                n /= 2;
            else if(n != 2 && n != 3 && n != 5 && n != 1)
                return false;
            else
                return true;
        }
    }
};
