// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-14 09:07
// Last modified: 2017-09-14 09:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        int max_length = 1, length = 1;
        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] > nums[i-1])
            {
                length++;
                max_length = max(max_length, length);
            }
            else
                length = 1;
        }
        return max_length;
    }
};
