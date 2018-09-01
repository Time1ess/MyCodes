class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int x = 2; x <= n; x++) {
            for (int y = 1; y < x; y++) {
                dp[x] = max(dp[x], max(y, dp[y]) * max(x-y, dp[x-y]));
            }
        }
        return dp[n];
    }
};
