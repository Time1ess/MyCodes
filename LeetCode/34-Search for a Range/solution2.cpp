// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-05 14:36
// Last modified: 2017-10-05 14:36
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans(2, -1);
        if(nums.empty())
            return ans;
        int l = 0, r = nums.size() - 1;
        while(l < r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] >= target)
                r = mid;
            else
                l = mid + 1;
        }
        if(nums[l] != target)
            return ans;
        ans[0] = l;
        
        r = nums.size() - 1;
        while(l < r)
        {
            int mid = l + (r - l) / 2 + 1;
            if(nums[mid] <= target)
                l = mid;
            else
                r = mid - 1;
        }
        ans[1] = l;
        return ans;
    }
};
