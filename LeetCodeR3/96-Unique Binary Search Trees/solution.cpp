class Solution {
public:
    int numTrees(int n) {
        if(n < 0) {
            return 0;
        }
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;
        dp[2] = 2;
        for(int cnt = 3; cnt <= n; cnt++) {
            for(int root = 1; root <= cnt; root++) {
                dp[cnt] += dp[root-1] * dp[cnt-root];
            }
        }
        return dp[n];
    }
};
