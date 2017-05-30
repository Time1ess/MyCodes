// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-18 16:46
// Last modified: 2017-04-18 16:46
// Filename: solution.cpp
// Description:
class Solution {
public:
    int find_peak(vector<int> &nums, int s, int e)
    {
        if(s >= e)
            return s;
        int m1 = (s + e) >> 1;
        int m2 = m1 + 1;
        if(nums[m1] > nums[m2])
            return find_peak(nums, s, m1);
        else
            return find_peak(nums, m2, e);
    }
    int findPeakElement(vector<int>& nums) {
        return find_peak(nums, 0, nums.size() - 1);
    }
};
