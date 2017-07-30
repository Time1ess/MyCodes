// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-30 16:21
// Last modified: 2017-07-30 16:21
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int maxA(int N) {
        if(N <= 6)
            return N;
        int dp[N+1] = {0};
        for(int i = 1; i <= 6; i++)
            dp[i] = i;
        for(int i = 7; i <= N; i++)
            dp[i] = max(dp[i - 4] * 3, dp[i - 5] * 4);
        return dp[N];
    }
};
