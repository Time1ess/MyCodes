class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int len = 3; len <= n; len++) {
            for(int left = 0; left + len <= n; left++) {
                int right = left + len - 1;
                for(int k = left + 1; k < right; k++) {
                    dp[left][right] = max(dp[left][right], dp[left][k] + nums[left] * nums[k] * nums[right] + dp[k][right]);
                }
            }
        }
        return dp[0][n-1];
    }
};
