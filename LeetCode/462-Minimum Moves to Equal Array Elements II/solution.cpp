// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-11-27 10:52
// Last modified: 2016-11-27 10:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int k = size/2;
        int ans = 0;
        for(int i=0; i < size; i++)
            ans += abs(nums[k]-nums[i]);
        return ans;
    }
};
