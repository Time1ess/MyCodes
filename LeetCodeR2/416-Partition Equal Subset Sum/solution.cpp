class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int m = nums.size();
        if(m <= 1)
            return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum & 0x1 == 1)
            return false;
        int n = sum / 2;
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for(int i = 1; i <= m; i++)
            for(int j = n; j >= nums[i-1]; j--)
                dp[j] = dp[j] || dp[j-nums[i-1]];
        return dp[n];
    }
};
