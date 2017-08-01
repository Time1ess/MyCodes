// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-01 09:20
// Last modified: 2017-08-01 09:20
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)
            return 0;
        else if(size == 1)
            return nums[0];
        else if(size == 2)
            return max(nums[0], nums[1]);
        int mpm1_i1, mpm1_e1, mpm2_i1, mpm2_e1, tmp;
        mpm1_i1 = nums[0];
        mpm2_i1 = nums[0];
        mpm1_e1 = nums[1];
        mpm2_e1 = 0;
        for(int i = 2; i < size - 1; i++)
        {
            //Max profit include robbing house 1
            tmp = max(mpm1_i1, mpm2_i1+nums[i]);
            mpm2_i1 = mpm1_i1;
            mpm1_i1 = tmp;
            //Max profit exclude robbing house 1
            tmp = max(mpm1_e1, mpm2_e1+nums[i]);
            mpm2_e1 = mpm1_e1;
            mpm1_e1 = tmp;
        }
        int mp_i1, mp_e1;
        mp_i1 = max(mpm1_i1, mpm2_i1);
        mp_e1 = max(mpm1_e1, mpm2_e1 + nums[size-1]);
        return max(mp_i1, mp_e1);
    }
};
