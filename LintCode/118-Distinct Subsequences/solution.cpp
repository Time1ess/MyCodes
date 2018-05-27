class Solution {
public:
    /*
     * @param : A string
     * @param : A string
     * @return: Count the number of distinct subsequences
     */
    int numDistinct(string S, string T) {
        // write your code here
        int m = S.length();
        int n = T.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for(int i = 0; i <= m; i++)
            dp[i][0] = 1;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++) {
                if (S[i-1] == T[j-1])
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j];
            }
        return dp[m][n];
    }
};
