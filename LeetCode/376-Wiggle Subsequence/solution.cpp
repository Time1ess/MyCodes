// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-06 15:40
// Last modified: 2017-06-06 15:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int size = nums.size();
        if(size < 2)
            return size;
        int last_down, last_up, down, up;
        up = down = 1;
        for(int i = 1; i < size; i++)
        {
            last_up = up;
            last_down = down;
            if(nums[i] > nums[i-1])
            {
                up = last_down + 1;
                down = last_down;
            }
            else if(nums[i] < nums[i-1])
            {
                down = last_up + 1;
                up = last_up;
            }
            else
            {
                down = last_down;
                up = last_up;
            }
        }
        return max(up, down);
    }
};
