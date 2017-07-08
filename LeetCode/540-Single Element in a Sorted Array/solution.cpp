// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-08 08:47
// Last modified: 2017-07-08 08:47
// Filename: solution.cpp
// Description:
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, r = nums.size();
        while(l < r - 1)
        {
            int m = l + (r - l) / 2;
            if(m % 2 == 0)
                if(nums[m] == nums[m-1])
                    r = m - 1;
                else
                    l = m;
            else
                if(nums[m] == nums[m-1])
                    l = m + 1;
                else
                    r = m;
        }
        return nums[l];
    }
};
