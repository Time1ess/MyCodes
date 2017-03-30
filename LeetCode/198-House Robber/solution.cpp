// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-30 10:04
// Last modified: 2017-03-30 10:04
// Filename: solution.cpp
// Description:
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        int mpm1, mpm2, mp;
        mp = mpm1 = mpm2 = 0;
        for(int i = 0; i < size; i++)
        {
            mp = max(mpm1, mpm2 + nums[i]);
            mpm2 = mpm1;
            mpm1 = mp;
        }
        return mp;
    }
};
