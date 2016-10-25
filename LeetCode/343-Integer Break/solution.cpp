// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-25 10:57
// Last modified: 2016-10-25 10:57
// Filename: solution.cpp
// Description:
class Solution {
public:
    int integerBreak(int n) {
        int dp[59];
        int tmp,t;
        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 2;
        for(int i=4; i<=n; i++)
        {
            tmp = 0;
            t = 0;
            for(int j=1; j<i; j++)
            {
                t = j * dp[i-j];
                tmp = tmp > t? tmp: t;
                t = j*(i-j);
                tmp = tmp > t? tmp: t;
            }
            dp[i] = tmp;
        }
        return dp[n];
    }
};
