class Solution {
public:
    /**
     * @param n: a positive integer
     * @return: An integer
     */
    int numSquares(int n) {
        // write your code here
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for(int x = 2; x <= n; x++) {
            int sqrt_x = sqrt(x);
            if(sqrt_x * sqrt_x == x) {
                dp[x] = 1;
                continue;
            } else {
                dp[x] = x;
            }
            for(int y = x - 1; y >= 1; y--) {
                dp[x] = min(dp[x], dp[y] + dp[x-y]);
            }
        }
        return dp[n];
    }
};
