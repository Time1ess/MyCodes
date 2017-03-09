// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-09 09:34
// Last modified: 2017-03-09 09:34
// Filename: solution.cpp
// Description:
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        if(size == 0)
            return 0;
        int dp[target+1] = {0};
        dp[0] = 1;
        for(int i = 1; i <= target; i++)
            for(int k = 0; k < size; k++)
            {
                if(nums[k] > i)
                    break;
                dp[i] += dp[i - nums[k]];
            }
        return dp[target];
    }
};
