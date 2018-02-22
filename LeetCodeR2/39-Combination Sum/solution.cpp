class Solution {
public:
    void dfs(vector<vector<int>> &ans, vector<int> &current, vector<int> &candidates, int idx, int s, int target)
    {
        if(s > target)
            return;
        if(idx == candidates.size())
        {
            if(s == target)
                ans.push_back(current);
            return;
        }
        dfs(ans, current, candidates, idx+1, s, target);
        current.push_back(candidates[idx]);
        dfs(ans, current, candidates, idx, s+candidates[idx], target);
        current.pop_back();
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> current;
        dfs(ans, current, candidates, 0, 0, target);
        return ans;
    }
};
