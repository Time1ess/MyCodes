// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-02 09:41
// Last modified: 2017-04-02 09:41
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        int valid = 0;
        for(int i = 0; i < size; i++)
            if(nums[i] != val)
                nums[valid++] = nums[i];
        return valid;
    }
};
