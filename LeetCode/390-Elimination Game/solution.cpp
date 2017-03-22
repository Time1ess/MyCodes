// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-22 11:13
// Last modified: 2017-03-22 11:13
// Filename: solution.cpp
// Description:
class Solution {
public:
    int lastRemaining(int n) {
        int s = 1, m = 1;
        bool c = true;
        while(n > 1)
        {
            if(c || n & 1)
                s += m;
            n >>= 1;
            c = !c;
            m *= 2;
        }
        return s;
    }
};
