// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-03 15:45
// Last modified: 2017-05-03 15:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i <= n; i++)
        {
            for(int k = 1; k * k <= i; k++)
                dp[i] = min(dp[i], dp[i - k * k] + 1);
        }
        return dp[n];
    }
};
