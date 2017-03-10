// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-10 21:28
// Last modified: 2017-03-10 21:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    void gen_perms(vector<vector<int>> &v, vector<int> &cv, int k, int size)
    {
        if(k == size)
        {
            v.push_back(cv);
            return;
        }
        for(int i = k; i < size; i++)
        {
            swap(cv[k], cv[i]);
            gen_perms(v, cv, k+1, size);
            swap(cv[k], cv[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        gen_perms(ans, nums, 0, nums.size());
        return ans;
    }
};
