class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        int tar = sum / 2;
        vector<vector<bool>> dp(n+1, vector<bool>(tar+1, false));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        for (int j = 0; j <= tar; j++) {
            dp[0][j] = false;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= tar; j++) {
                dp[i][j] = dp[i-1][j];
                if (j >= nums[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j-nums[i-1]];
                }
            }
        }
        return dp[n][tar];
    }
};
