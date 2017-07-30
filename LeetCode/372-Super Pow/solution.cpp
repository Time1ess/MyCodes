// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-30 14:25
// Last modified: 2017-07-30 14:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    int powmod(int a, int k)
    {
        a %= 1337;
        int res = 1;
        for(int i = 0; i < k; i++)
            res = (res * a) % 1337;
        return res;
    }
    int superPow(int a, vector<int>& b) {
        if(b.empty())
            return 1;
        int digit = b.back();
        b.pop_back();
        return powmod(superPow(a, b), 10) * powmod(a, digit) % 1337;
    }
};
