class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        for(int i = 1; i <= target; i++)
        {
            for(auto num: nums)
                if(i > num)
                    dp[i] += dp[i-num];
                else if(i == num)
                    dp[i]++;
        }
        return dp[target];
    }
};
