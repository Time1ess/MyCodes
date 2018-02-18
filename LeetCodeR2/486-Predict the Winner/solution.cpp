class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> asums(n+1, 0);
        for(int i = 0; i < n; i++)
            asums[i+1] = asums[i] + nums[i];
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++)
            dp[i][i] = nums[i];
        for(int len = 2; len <= n; len++)
            for(int i = 0; i + len - 1 < n; i++)
            {
                int j = i + len - 1;
                dp[i][j] = max(asums[j] - asums[i] - dp[i][j-1] + nums[j],
                               asums[j+1] - asums[i+1] - dp[i+1][j] + nums[i]);
            }
        return (2 * dp[0][n - 1]) >= asums[n];
    }
};
