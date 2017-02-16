// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-16 18:54
// Last modified: 2017-02-16 18:54
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int size = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int s = (sum + S);
        if(sum < S || s & 1)
            return 0;
        s >>= 1;
        int dp[s+1] = {0};
        dp[0] = 1;
        for(int num : nums)
            for(int k = s; k >= num; k--)
                dp[k] += dp[k - num];
        return dp[s];
        // dp[k]: vector数组中可以构成值大小为k的组合种数
        // P集合: vector数组中取正的数的和
        // N集合: vector数组中取负的数的和
        // sum: vector数组的和
        // P - N = S
        // P - N + P + N = S + P + N
        // 2 * P = S + sum
        // P = (S + sum) / 2
        // 题目转化为求vector数组中的一个子集，使得该子集
        // 的和刚好为(S + sum) / 2，P集合的个数即为该子集
        // 的种数
    }
};
