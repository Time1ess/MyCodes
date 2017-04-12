// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 09:17
// Last modified: 2017-04-12 09:17
// Filename: solution.cpp
// Description:
class Solution {
public:
    void find_comb(vector<vector<int>> &ans, vector<int> &current, vector<int> &candidates, int target, int k, int size)
    {
        if(k == size || target == 0)
        {
            if(target == 0)
                ans.push_back(current);
            return;
        }
        for(int i = k; i < size && candidates[i] <= target; i++)
        {
            current.push_back(candidates[i]);
            find_comb(ans, current, candidates, target-candidates[i], i, size);
            current.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> current;
        int size = candidates.size();
        if(size == 0)
            return ans;
        sort(candidates.begin(), candidates.end());
        find_comb(ans, current, candidates, target, 0, size);
        return ans;
    }
};
