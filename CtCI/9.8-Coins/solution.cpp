class Coins {
public:
    int countWays(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        static const vector<int> coins = {1, 5, 10, 25};
        for(auto coin: coins) {
            for(int v = coin; v <= n; v++) {
                dp[v] = (dp[v] + dp[v-coin]) % 1000000007;
            }
        }
        return dp[n];
    }
};
