class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1, 0);
        sort(nums.begin(), nums.end());
        for (int i = 1; i <= target; i++) {
            for (auto x : nums) {
                if (x > i) {
                    break;
                } else if (x == i) {
                    dp[i] += 1;
                } else {
                    dp[i] += dp[i-x];
                }
            }
        }
        return dp[target];
    }
};
