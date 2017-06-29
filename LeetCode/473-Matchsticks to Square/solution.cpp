// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 11:37
// Last modified: 2017-06-27 11:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool can_done(vector<int> &nums, vector<int> &sides, int idx, int &target)
    {
        if(idx == nums.size())
            return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3] && sides[3] == target;
        for(int i = 0; i < 4; i++)
        {
            if(sides[i] + nums[idx] <= target)
            {
                sides[i] += nums[idx];
                if(can_done(nums, sides, idx+1, target))
                    return true;
                sides[i] -= nums[idx];
            }
        }
        return false;
    }
    bool makesquare(vector<int>& nums) {
        int all_sum = accumulate(nums.begin(), nums.end(), 0);
        if(all_sum == 0 || all_sum % 4 != 0)
            return false;
        int target = all_sum / 4;
        vector<int> sides(4, 0);
        return can_done(nums, sides, 0, target);
    }
};
