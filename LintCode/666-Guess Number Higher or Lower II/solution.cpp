class Solution {
public:
    /**
     * @param n: An integer
     * @return: how much money you need to have to guarantee a win
     */
    int guess(vector<vector<int>>& dp, int s, int e) {
        if(s >= e) {
            return 0;
        }
        if(dp[s][e] != 0) {
            return dp[s][e];
        }
        int res = INT_MAX;
        for(int i = s; i <= e; i++) {
            res = min(res, i + max(guess(dp, s, i - 1), guess(dp, i + 1, e)));
        }
        dp[s][e] = res;
        return res;
    }
    int getMoneyAmount(int n) {
        // write your code here
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        return guess(dp, 1, n);
    }
};
