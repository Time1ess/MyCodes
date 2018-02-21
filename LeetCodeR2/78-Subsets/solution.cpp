class Solution {
public:
    void backtrack(vector<vector<int>> &ans, vector<int> &current, vector<int> &nums, int idx, int n)
    {
        if(idx == n)
        {
            ans.push_back(current);
            return;
        }
        // exclude nums[idx]
        backtrack(ans, current, nums, idx+1, n);
        // include nums[idx]
        current.push_back(nums[idx]);
        backtrack(ans, current, nums, idx+1, n);
        current.pop_back();
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> current;
        backtrack(ans, current, nums, 0, nums.size());
        return ans;
    }
};
