// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-30 08:45
// Last modified: 2017-05-30 08:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    int find_length(vector<int> &nums, int *memo, int &size, int k)
    {
        if(memo[k] > 0)
            return memo[k];
        else if(memo[k] == -1)
            return 0;
        memo[k] = -1;
        memo[k] = 1 + find_length(nums, memo, size, nums[k]);
        return memo[k];
    }
    int arrayNesting(vector<int>& nums) {
        int size = nums.size();
        int memo[size];
        for(int i = 0; i < size; i++)
            memo[i] = -2;
        int max_length = 0;
        for(int i = 0; i < size; i++)
            max_length = max(max_length, find_length(nums, memo, size, i));
        return max_length;
    }
};
