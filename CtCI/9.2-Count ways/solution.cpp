class Robot {
public:
    int countWays(int x, int y) {
        // write code here
        vector<vector<int>> dp(x, vector<int>(y, 0));
        dp[0][0] = 1;
        for(int i = 1; i < x; i++)
            dp[i][0] = 1;
        for(int j = 1; j < y; j++)
            dp[0][j] = 1;
        for(int i = 1; i < x; i++) {
            for(int j = 1; j < y; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[x-1][y-1];
    }
};
