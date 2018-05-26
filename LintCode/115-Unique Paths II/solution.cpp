class Solution {
public:
    /**
     * @param obstacleGrid: A list of lists of integers
     * @return: An integer
     */
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0)
            return 1;
        int n = obstacleGrid[0].size();
        if (n == 0)
            return 1;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                if(obstacleGrid[i][j] == 1)
                    continue;
                if(i == 0 && j == 0)
                    dp[i][j] = 1;
                else if(i == 0 && j != 0)
                    dp[i][j] = dp[i][j-1];
                else if(i != 0 && j == 0)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        return dp[m-1][n-1];
    }
};
