// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-30 15:31
// Last modified: 2017-07-30 15:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int ans = m & n;
        int k = 0;
        int remain = n - m;
        int mask = 0xffffffff;
        while(remain)
        {
            ans &= (mask^(1<<k));
            k++;
            remain /= 2;
        }
        return ans;
    }
};
