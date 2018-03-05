class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        if(n == 0 || m == 0)
            return max(n, m);
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));  // dp[i][j]: minimum deletions for s1 of len i and s2 of len j
        for(int i = 1; i <= n; i++)
            dp[i][0] = i;
        for(int j = 1; j <= m; j++)
            dp[0][j] = j;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(dp[i-1][j] + 1, min(dp[i][j-1] + 1, dp[i-1][j-1] + 2));
        return dp[n][m];
    }
};
