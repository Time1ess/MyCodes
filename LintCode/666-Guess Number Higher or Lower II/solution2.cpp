class Solution {
public:
    /**
     * @param n: An integer
     * @return: how much money you need to have to guarantee a win
     */
    int getMoneyAmount(int n) {
        // write your code here
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for(int len = 2; len <= n; len++) {
            for(int s = 1; s + len <= n + 1; s++) {
                int e = s + len - 1;
                dp[s][e] = INT_MAX;
                for(int k = s; k <= e; k++) {
                    int t = k;
                    if(s <= k - 1 && k + 1 <= e) {
                        t += max(dp[s][k-1], dp[k+1][e]);
                    } else if(s <= k - 1) {
                        t += dp[s][k-1];
                    } else if(k + 1 <= e){
                        t += dp[k+1][e];
                    }
                    dp[s][e] = min(dp[s][e], t);
                }
            }
        }
        return dp[1][n];
    }
};
