class Solution {
public:
    /**
     * @param N: an integer
     * @return: return an integer
     */
    int maxA(int N) {
        // write your code here
        vector<int> dp(51, 0);
        for(int i = 1; i <= N; i++)
        {
            dp[i] = i;
            for(int k = 1; k <= i - 3; k++)
                dp[i] = max(dp[i], dp[k] * (i - 1 - k));
        }
        return dp[N];
    }
};
