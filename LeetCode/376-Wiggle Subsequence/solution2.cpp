// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-06 15:49
// Last modified: 2017-06-06 15:49
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int size = nums.size();
        if(size < 2)
            return size;
        int down, up;
        up = down = 1;
        for(int i = 1; i < size; i++)
            if(nums[i] > nums[i-1])
                up = down + 1;
            else if(nums[i] < nums[i-1])
                down = up + 1;
        return max(up, down);
    }
};
