// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-30 16:18
// Last modified: 2017-07-30 16:18
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxA(int N) {
        int dp[N+1] = {0};
        for(int i = 1; i <= N; i++)
        {
            dp[i] = i;
            for(int j = 3; j < i; j++)
                dp[i] = max(dp[i], dp[i - j] * (j - 1));
        }
        return dp[N];
    }
};
