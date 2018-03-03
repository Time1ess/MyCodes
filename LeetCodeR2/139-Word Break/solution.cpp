class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<vector<bool>> dp(n + 1, vector<bool>(n + 1, false));
        set<string> words(wordDict.begin(), wordDict.end());
        for(int len = 1; len <= n; len++)
            for(int i = 0; i <= n - len; i++)
            {
                int j = i + len;
                if(words.find(s.substr(i, len)) != words.end())
                    dp[i][j] = true;
                else
                    for(int k = i + 1; k < j; k++)
                        dp[i][j] = dp[i][j] || dp[i][k] && dp[k][j];
            }
        return dp[0][n];
    }
};
