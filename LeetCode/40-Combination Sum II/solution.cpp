// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-09 09:59
// Last modified: 2017-08-09 09:59
// Filename: solution.cpp
// Description:
class Solution {
public:
    void find_combinations(set<vector<int>> &combinations, vector<int> &candidates, vector<int> &current, int target, int index)
    {
        if(target == 0)
        {
            combinations.insert(current);
            return;
        }
        if(index == candidates.size() || candidates[index] > target)
            return;
        // Select this element
        current.push_back(candidates[index]);
        if(combinations.find(current) == combinations.end())
            find_combinations(combinations, candidates, current, target - candidates[index], index + 1);
        current.pop_back();
        // Skip this element
        find_combinations(combinations, candidates, current, target, index + 1);
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> current;
        sort(candidates.begin(), candidates.end());
        set<vector<int>> combinations;
        find_combinations(combinations, candidates, current, target, 0);
        vector<vector<int>> ans(combinations.begin(), combinations.end());
        return ans;
    }
};
