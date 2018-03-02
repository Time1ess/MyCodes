class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: Another string
     * @return: whether s2 is a scrambled string of s1
     */
    bool isScramble(string &s1, string &s2) {
        // write your code here
        if(s1.length() != s2.length())
            return false;
        int n = s1.length();
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dp[i][j][1] = s1[i] == s2[j];
        for(int len = 2; len <= n; len++)
            for(int i = 0; i < n - len + 1; i++)
                for(int j = 0; j < n - len + 1; j++)
                    for(int k = 1; k < len; k++)
                        dp[i][j][len] = dp[i][j][len]
                            || (dp[i][j][k] && dp[i+k][j+k][len-k])
                            || (dp[i][j+len-k][k] && dp[i+k][j][len-k]);
        return dp[0][0][n];
    }
};
