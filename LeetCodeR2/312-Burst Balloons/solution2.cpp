class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int len = 2; len < n; len++)
        {
            for(int left = 0; left < n - len; left++)
            {
                int right = left + len;
                for(int k = left + 1; k < right; k++)
                    dp[left][right] = max(dp[left][right], nums[left] * nums[k] * nums[right] + dp[left][k] + dp[k][right]);
            }
        }
        return dp[0][n-1];
    }
};
