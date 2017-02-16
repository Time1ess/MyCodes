// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-16 18:13
// Last modified: 2017-02-16 18:13
// Filename: solution.cpp
// Description:
class Solution {
public:
    void dfs_cnt(vector<int>& nums, int s, int idx, int& size, int& cnt)
    {
        if(idx == size)
        {
            if(s == 0)
                cnt++;
            return;
        }
        dfs_cnt(nums, s-nums[idx], idx+1, size, cnt);
        dfs_cnt(nums, s+nums[idx], idx+1, size, cnt);
    }
    int findTargetSumWays(vector<int>& nums, int S) {
        int cnt = 0;
        int size = nums.size();
        dfs_cnt(nums, S, 0, size, cnt);
        return cnt;
    }
};
