class Solution {
public:
    void backtracking(vector<int>& nums, vector<vector<int>>& ans, vector<int>& current, int idx, int n) {
        if (idx == n) {
            ans.push_back(current);
            return;
        }
        int j = idx;
        while (j < n && nums[idx] == nums[j]) {
            j++;
        }
        int cnt = j - idx;
        backtracking(nums, ans, current, j, n);  // No nums[idx]
        for (int c = 1; c <= cnt; c++) {
            current.push_back(nums[idx]);
            backtracking(nums, ans, current, j, n);
        }
        for (int c = 1; c <= cnt; c++) {
            current.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> current;
        backtracking(nums, ans, current, 0, nums.size());
        return ans;
    }
};
