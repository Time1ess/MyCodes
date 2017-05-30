// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-18 16:49
// Last modified: 2017-04-18 16:49
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        int m1, m2;
        while(low < high)
        {
            m1 = (low + high) >> 1;
            m2 = m1 + 1;
            if(nums[m1] > nums[m2])
                high = m1;
            else
                low = m2;
        }
        return low;
    }
};
