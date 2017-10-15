// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-15 14:23
// Last modified: 2017-10-15 14:23
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)
            return true;
        bool dp[size] = {false};
        dp[size - 1] = true;
        for(int i = size - 2; i >= 0; i--)
        {
            for(int step = 1; step <= nums[i] && i + step < size; step++)
                if(dp[i+step])
                {
                    dp[i] = true;
                    break;
                }
        }
        return dp[0];
    }
};
