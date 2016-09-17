// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 13:35
// Last modified: 2016-09-17 13:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    int getSum(int a, int b) {
        int tmp;
        while(b!=0)
        {
            tmp=a^b;
            b=(a&b)<<1;
            a=tmp;
        }
        return a;
    }
};
