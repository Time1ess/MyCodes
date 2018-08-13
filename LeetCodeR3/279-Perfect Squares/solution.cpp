class Solution {
public:
    int numSquares(int n) {
        if (n == 1) {
            return 1;
        };
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int x = 2; x <= n; x++) {
            int sqrt_x = sqrt(x);
            if (sqrt_x * sqrt_x == x) {
                dp[x] = 1;
                continue;
            }
            dp[x] = INT_MAX;
            for (int y = 1; y * y < x; y++) {
                dp[x] = min(dp[x], 1 + dp[x - y * y]);
            }
        }
        return dp[n];
    }
};
