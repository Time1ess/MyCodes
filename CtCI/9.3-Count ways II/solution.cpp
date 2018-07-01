class Robot {
public:
    int countWays(vector<vector<int> > map, int x, int y) {
        // write code here
        vector<vector<int>> dp(x, vector<int>(y, 0));
        if(map[0][0] == 0)
            return 0;
        dp[0][0] = 1;
        for(int i = 1; i < x; i++)
            if(map[i][0] == 0)  // Obstacle
                dp[i][0] = 0;
            else
                dp[i][0] = dp[i-1][0];
        for(int j = 1; j < y; j++)
            if(map[0][j] == 0)  // Obstacle
                dp[0][j] = 0;
            else
                dp[0][j] = dp[0][j-1];
        for(int i = 1; i < x; i++) {
            for(int j = 1; j < y; j++) {
                if(map[i][j] == 0)  // Obstacle
                    dp[i][j] = 0;
                else
                    dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % 1000000007;
            }
        }
        return dp[x-1][y-1];
    }
};
