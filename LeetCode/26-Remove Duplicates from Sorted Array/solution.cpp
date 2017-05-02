// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-02 15:25
// Last modified: 2017-05-02 15:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(size <= 1)
            return size;
        int i = 0, j = 0;
        for(;j < size; j++)
        {
            if(nums[i] != nums[j])
                nums[++i] = nums[j];
        }
        return i+1;
    }
};
