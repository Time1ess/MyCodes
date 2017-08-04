// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-04 10:07
// Last modified: 2017-08-04 10:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<int> ans;
        if(nums.size() == 0)
            return ans;
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int dp[size] = {0};
        int max_idx = 0;
        for(int i = 0; i < size; i++)
        {
            for(int j = i; j >= 0; j--)
                if(nums[i] % nums[j] == 0)
                    dp[i] = max(dp[i], dp[j] + 1);
            max_idx = dp[max_idx] > dp[i] ? max_idx: i;
        }
        int dividend = nums[max_idx];
        int cnt = dp[max_idx];
        for(int i = max_idx; i >= 0; i--)
            if(dividend % nums[i] == 0 && dp[i] == cnt)
            {
                ans.push_back(nums[i]);
                dividend = nums[i];
                cnt--;
            }
        return ans;
    }
};
