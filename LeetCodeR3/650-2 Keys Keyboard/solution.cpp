class Solution {
public:
    int minSteps(int n) {
        if (n == 1) {
            return 0;
        }
        vector<int> dp(n+1, 0);
        for (int x = 2; x <= n; x++) {
            dp[x] = x;
            for (int y = x - 1; y > 1; y--) {
                if (x % y == 0) {
                    dp[x] = dp[y] + x / y;
                    break;
                }
            }
        }
        return dp[n];
    }
};
