// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-03 08:56
// Last modified: 2017-06-03 08:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    void gen_subsets(vector<int> &nums, vector<vector<int>> &ans, vector<int> &current, int idx)
    {
        ans.push_back(current);
        for(int i = idx; i < nums.size(); i++)
        {
            if(i == idx || nums[i] != nums[i-1])
            {
                current.push_back(nums[i]);
                gen_subsets(nums, ans, current, i+1);
                current.pop_back();
            }
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> current;
        int size = nums.size();
        sort(nums.begin(), nums.end());
        gen_subsets(nums, ans, current, 0);
        return ans;
    }
};
