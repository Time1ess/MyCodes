class Solution {
public:
    int integerBreak(int n) {
        if(n < 2)
            return 1;
        else if(n == 2)
            return 1;
        vector<int> dp(59, 0);
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++)
            for(int j = i - 1; j >= 2; j--)
                dp[i] = max(dp[i], max(j, dp[j]) * max(i - j, dp[i - j]));
        return dp[n];
    }
};;
