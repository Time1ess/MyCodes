class Solution {
public:
    bool wordBreak(string S, vector<string>& wordDict) {
        int n = S.length();
        vector<vector<bool>> dp(n, vector<bool>(n, 0));
        unordered_set<string> words;
        for (auto x: wordDict) {
            words.insert(x);
        }
        for (int len = 1; len <= n; len++) {
            for(int s = 0; s + len <= n; s++) {
                int e = s + len - 1;
                // subs[s,e]
                if (words.find(S.substr(s, len)) != words.end()) {
                    dp[s][e] = true;
                    continue;
                }
                for (int k = s; k < e; k++) {
                    // subs[s, k], subs[k+1, e]
                    dp[s][e] = dp[s][e] || (dp[s][k] && dp[k+1][e]);
                }
            }
        }
        return dp[0][n-1];
    }
};
