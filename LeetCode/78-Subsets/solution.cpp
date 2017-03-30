// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-30 08:52
// Last modified: 2017-03-30 08:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    void gen_subsets(vector<int> &nums, vector<vector<int>> &ans, vector<int> &res, int s, int k)
    {
        if(k == 0)
        {
            ans.push_back(res);
            return;
        }
        for(int i = s; i < nums.size(); i++)
        {
            res.push_back(nums[i]);
            gen_subsets(nums, ans, res, i+1, k-1);
            res.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> res;
        for(int i = 0; i <= nums.size(); i++)
            gen_subsets(nums, ans, res, 0, i);
        return ans;
    }
};
