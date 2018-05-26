class Solution {
public:
    /**
     * @param m: positive integer (1 <= m <= 100)
     * @param n: positive integer (1 <= n <= 100)
     * @return: An integer
     */
    int uniquePaths(int m, int n) {
        // write your code here
        vector<int> dp(n, 0);
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                if(j == 0)
                    dp[j] = 1;
                else if(i == 0)
                    dp[j] = dp[j-1];
                else
                    dp[j] += dp[j-1];
            }
        return dp[n-1];
    }
};
