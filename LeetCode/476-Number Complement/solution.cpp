// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-01-16 21:55
// Last modified: 2017-01-16 21:55
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findComplement(int num) {
        int tn = num;
        int mask = 0;
        while(num)
        {
            mask = mask<<1|1;
            num>>=1;
        }
        return tn^mask;
    }
};
