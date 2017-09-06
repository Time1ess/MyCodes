// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-06 11:12
// Last modified: 2017-09-06 11:12
// Filename: solution.cpp
// Description:
class Solution {
public:
    void dfs(vector<vector<int>> &ans, vector<int> nums, int i, int &size)
    {
        if(i == size - 1)
        {
            ans.push_back(nums);
            return;
        }
        for(int k = i; k < size; k++)
        {
            if(i != k && nums[i] == nums[k])
                continue;
            swap(nums[i], nums[k]);
            dfs(ans, nums, i+1, size);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int i = 0, size = nums.size();
        dfs(ans, nums, i, size);
        return ans;
    }
};
