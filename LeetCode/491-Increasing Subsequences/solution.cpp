// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-28 09:36
// Last modified: 2017-03-28 09:36
// Filename: solution.cpp
// Description:
class Solution {
public:
    void find_subsequences(set<vector<int>> &showups, vector<int> &res, int idx, vector<int> &nums)
    {
        if(res.size() >= 2)
            showups.insert(res);
        for(int i = idx; i < nums.size(); i++)
        {
            if(res.size() == 0 || res.back() <= nums[i])
            {
                res.push_back(nums[i]);
                find_subsequences(showups, res, i+1, nums);
                res.pop_back();
            }
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> showups;
        vector<vector<int>> ans;
        vector<int> res;
        find_subsequences(showups, res, 0, nums);
        for(auto x:showups)
            ans.push_back(x);
        return ans;
    }
};
