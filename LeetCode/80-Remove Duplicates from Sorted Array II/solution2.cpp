// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-11 09:08
// Last modified: 2017-05-11 09:08
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int tail = 0;
        for(auto num: nums)
            if(tail < 2 || num > nums[tail - 2])
                nums[tail++] = num;
        return tail;
    }
};
