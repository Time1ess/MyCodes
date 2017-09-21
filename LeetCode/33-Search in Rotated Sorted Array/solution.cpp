// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-21 09:00
// Last modified: 2017-09-21 09:00
// Filename: solution.cpp
// Description:
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[left] < nums[mid])
            {
                if(target >= nums[left] && target < nums[mid])
                    right = mid;
                else
                    left = mid + 1;
            }
            else
            {
                if(target > nums[mid] && target <= nums[right - 1])
                    left = mid + 1;
                else
                    right = mid;
            }
        }
        return -1;
    }
};
