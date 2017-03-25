// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-25 10:10
// Last modified: 2017-03-25 10:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMin(vector<int>& nums) {
        int s, e, m;
        s = 0;
        e = nums.size() - 1;
        while(s < e)
        {
            if(nums[s] < nums[e])
                return nums[s];
            m = (s + e) >> 1;
            if(nums[m] >= nums[s])
                s = m + 1;
            else
                e = m;
        }
        return nums[s];
    }
};
