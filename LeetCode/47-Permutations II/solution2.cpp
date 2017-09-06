// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-06 11:19
// Last modified: 2017-09-06 11:19
// Filename: solution2.cpp
// Description:
class Solution {
public:
    void dfs(vector<vector<int>> &ans, vector<int> &nums, vector<int> &current, vector<bool> &used)
    {
        if(current.size() == nums.size())
        {
            ans.push_back(current);
            return;
        }
        for(int i = 0; i < nums.size(); i++)
        {
            if(used[i])
                continue;
            if(i > 0 && nums[i-1] == nums[i] && used[i-1] == false)
                continue;
            used[i] = true;
            current.push_back(nums[i]);
            dfs(ans, nums, current, used);
            current.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<bool> used(nums.size(), false);
        vector<int> current;
        dfs(ans, nums, current, used);
        return ans;
    }
};
