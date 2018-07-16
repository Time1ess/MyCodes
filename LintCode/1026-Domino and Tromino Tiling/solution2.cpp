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
        vector<int> dp(N+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        const static int mod = 1e9 + 7;
        for(int i = 3; i <= N; i++) {
            dp[i] = ((2 * dp[i-1]) % mod + dp[i-3]) % mod;
        }
        return dp[N];
    }
};
