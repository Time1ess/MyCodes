// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-02 14:56
// Last modified: 2017-05-02 14:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int trailingZeroes(int n) {
        int cnt = 0;
        long k = 5;
        while(n >= k)
        {
            cnt += n / k;
            k *= 5;
        }
        return cnt;
    }
};
