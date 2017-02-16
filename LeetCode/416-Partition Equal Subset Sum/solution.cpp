// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-16 19:03
// Last modified: 2017-02-16 19:03
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // P1: vector数组的某些数构成集合的和
        // P2: vector数组中除了P1以外的所有数的集合的和
        // sum: vector数组求和
        // P1 + P2 = sum
        // P1 = P2 = sum / 2
        // 转化为求vector数组中是否存在子集，使其和为 sum / 2
        int half_sum = accumulate(nums.begin(), nums.end(), 0);
        if(half_sum & 1)
            return false;
        half_sum >>= 1;
        int dp[half_sum+1] = {1};
        for(int num: nums)
            for(int k=half_sum; k >= num; k--)
                dp[k] += dp[k-num];
        return dp[half_sum];
    }
};
