class GoUpstairs {
public:
    int countWays(int n) {
        // write code here
        vector<long long> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        for(int i = 4; i <= n; i++) {
            dp[i] = (dp[i-3] + dp[i-2] + dp[i-1]) % 1000000007;
        }
        return dp[n];
    }
};
