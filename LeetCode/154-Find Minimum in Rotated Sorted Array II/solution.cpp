// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-23 11:37
// Last modified: 2017-04-23 11:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        int m;
        while(l < r)
        {
            m = l + (r - l) / 2;
            if(nums[m] > nums[r])
                l = m + 1;
            else if(nums[m] < nums[r])
                r = m;
            else
                r--;
        }
        return nums[l];
    }
};
