// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-01-16 21:41
// Last modified: 2017-01-16 21:41
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max_cnt = 0, cur_cnt = 0;
        for(int i=0; i < nums.size(); i++)
        {
            if(nums[i] == 1)
                cur_cnt++;
            else
            {
                max_cnt = max(max_cnt, cur_cnt);
                cur_cnt = 0;
            }
        }
        return max(max_cnt, cur_cnt);
    }
};
