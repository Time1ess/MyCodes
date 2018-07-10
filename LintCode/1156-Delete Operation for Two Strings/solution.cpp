class Solution {
public:
    /**
     * @param word1: a string
     * @param word2: a string
     * @return: return a integer
     */
    int minDistance(string &word1, string &word2) {
        // write your code here
        int n = word1.length(), m = word2.length();
        if(n == 0 || m == 0)
            return max(n, m);
        // dp[i][j]: minimum distance for word1[:i) and word2[:j)
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; i++)
            dp[i][0] = i;
        for(int j = 1; j <= m; j++)
            dp[0][j] = j;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
            }
        }
        return dp[n][m];
    }
};
