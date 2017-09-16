// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-16 09:51
// Last modified: 2017-09-16 09:51
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.size() == 0)
            return false;
        int l = 0, r = nums.size() - 1, m;
        while(l < r)
        {
            m = l + (r - l) / 2;
            if(target == nums[m])
                return true;
            else if(nums[m] > nums[r])
                if(target < nums[m] && target >= nums[l])
                    r = m;
                else
                    l = m + 1;
            else if(nums[m] < nums[r])
                if(target > nums[m] && target <= nums[r])
                    l = m + 1;
                else
                    r = m;
            else
                r--;
        }
        return nums[l] == target;
    }
};
