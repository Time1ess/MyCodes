// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-05 14:23
// Last modified: 2017-10-05 14:23
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        int right = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
        if(left > right)
            left = right = -1;
        return vector<int>{left, right};
    }
};
