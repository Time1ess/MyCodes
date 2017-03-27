// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-25 10:19
// Last modified: 2017-03-25 10:19
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int dp = 0, mmax;
        if(nums.size() == 1)
            return nums[0];
        for(int i = 0; i < nums.size(); i++)
        {
            dp += nums[i];
            if(dp < nums[i])
                dp = nums[i];
            mmax = max(dp, mmax);
        }
        return mmax;
    }
};
