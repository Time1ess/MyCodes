// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-15 14:26
// Last modified: 2017-10-15 14:26
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int i = 0, size = nums.size();
        for(int reach = 0; i < size && i <= reach; i++)
            reach = max(i + nums[i], reach);
        return i == size;
    }
};
