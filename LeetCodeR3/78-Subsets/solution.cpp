class Solution {
public:
    void combinations(vector<int>& nums, vector<vector<int>>& ans, vector<int>& cur, int idx, int n) {
        if(idx == n) {
            ans.push_back(cur);
            return;
        }
        // Skip nums[idx]
        combinations(nums, ans, cur, idx + 1, n);
        // Select nums[idx]
        cur.push_back(nums[idx]);
        combinations(nums, ans, cur, idx + 1, n);
        cur.pop_back();
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> cur;
        combinations(nums, ans, cur, 0, nums.size());
        return ans;
    }
};
