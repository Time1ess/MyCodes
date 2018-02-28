class Solution {
public:
    /**
     * @param m: the number of eggs
     * @param n: the number of floors
     * @return: the number of drops in the worst case
     */
    int dropEggs2(int m, int n) {
        // write your code here
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));
        dp[0][0] = 0;
        for(int i = 1; i <= m; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 1;
        }
        for(int j = 1; j <= n; j++)
            dp[1][j] = j;
        for(int i = 2; i <= m; i++)
            for(int j = 2; j <= n; j++)
                for(int k = 1; k < j; k++)
                    dp[i][j] = min(dp[i][j], 1 + max(dp[i-1][k-1], dp[i][j-k]));
        return dp[m][n];
    }
};
