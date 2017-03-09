// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-09 09:10
// Last modified: 2017-03-09 09:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)
            return 0;
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int dp[size+2][size+2] = {0};
        for(int len = 1; len <= size; len++)
            for(int left = 1; left + len - 1 <= size; left++)
            {
                int right = left + len - 1;
                for(int k = left; k <= right; k++)
                    dp[left][right] = max(dp[left][right], nums[left-1] * nums[k] * nums[right+1] + dp[left][k-1] + dp[k+1][right]);
            }
        return dp[1][size];
    }
};
