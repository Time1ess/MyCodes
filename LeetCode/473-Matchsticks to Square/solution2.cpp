// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 11:51
// Last modified: 2017-06-27 11:51
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool can_done(vector<int> &nums, vector<int> &sides, int idx, int &target)
    {
        if(idx == nums.size())
            return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3] && sides[3] == target;
        for(int i = 0; i < 4; i++)
        {
            if(sides[i] + nums[idx] > target)
                continue;
            int j = i;
            while(--j >= 0)
                if(sides[i] == sides[j])
                    break;
            if(j != -1)
                continue;
            sides[i] += nums[idx];
            if(can_done(nums, sides, idx+1, target))
                return true;
            sides[i] -= nums[idx];
        }
        return false;
    }
    bool makesquare(vector<int>& nums) {
        int all_sum = accumulate(nums.begin(), nums.end(), 0);
        if(all_sum == 0 || all_sum % 4 != 0)
            return false;
        int target = all_sum / 4;
        vector<int> sides(4, 0);
        sort(nums.begin(), nums.end(), greater<int>());
        return can_done(nums, sides, 0, target);
    }
};
