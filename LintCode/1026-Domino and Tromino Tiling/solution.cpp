class Solution {
public:
    /**
     * @param N: a integer
     * @return: return a integer
     */
    int numTilings(int N) {
        // write your code here
        if(N == 1) {
            return 1;
        }
        vector<vector<long long>> dp(N+1, vector<long long>(2, 0));
        dp[1][0] = 1;
        dp[2][0] = 2;
        dp[2][1] = 2;
        const static int mod = 1e9 + 7;
        for(int i = 3; i <= N; i++) {
            dp[i][0] = (dp[i-1][0] + dp[i-2][0] + dp[i-1][1]) % mod;
            dp[i][1] = (2 * dp[i-2][0] + dp[i-1][1]) % mod;
        }
        return dp[N][0];
    }
};
