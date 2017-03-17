// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-17 14:49
// Last modified: 2017-03-17 14:49
// Filename: solution.cpp
// Description:
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m <= 0 || n <= 0)
            return 0;
        int dp[m + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        dp[0][1] = 1;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
        return dp[m][n];
    }
};
