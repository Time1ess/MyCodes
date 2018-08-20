class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (auto x: coins) {
                if (i < x || dp[i-x] == -1) {
                    continue;
                }
                dp[i] = min(dp[i], 1 + dp[i-x]);
            }
            if (dp[i] == INT_MAX) {
                dp[i] = -1;
            }
        }
        return dp[amount] == -1 ? -1 : dp[amount];
    }
};
