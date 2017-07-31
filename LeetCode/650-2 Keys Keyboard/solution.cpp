// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-31 09:25
// Last modified: 2017-07-31 09:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minSteps(int n) {
        int dp[n + 1] = {0};
        for(int i = 2; i <= n; i++)
        {
            dp[i] = i;
            for(int j = i / 2; j > 1; j--)
                if(i % j == 0)
                {
                    dp[i] = dp[j] + i / j;
                    break;
                }
        }
        return dp[n];
    }
};
