class Solution {
public:
    void generateCombinations(vector<int>& nums, vector<vector<int>>& ans, vector<int>& cur, int idx, int n,
                              int cur_sum, int target) {
        if(idx == n) {
            if(cur_sum == target) {
                ans.push_back(cur);
            }
            return;
        }
        generateCombinations(nums, ans, cur, idx + 1, n, cur_sum, target);
        int cnt = (target - cur_sum) / nums[idx];
        for(int k = 1; k <= cnt; k++) {
            cur.push_back(nums[idx]);
            generateCombinations(nums, ans, cur, idx + 1, n, cur_sum + nums[idx] * k, target);
        }
        for(int k = 1; k <= cnt; k++) {
            cur.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> cur;
        generateCombinations(candidates, ans, cur, 0, candidates.size(), 0, target);
        return ans;
    }
};
