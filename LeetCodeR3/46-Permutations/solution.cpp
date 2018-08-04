class Solution {
public:
    void generate_permutations(vector<vector<int>>& ans, vector<int>& nums, int idx, int n) {
        if(idx == n) {
            ans.push_back(nums);
        }
        for(int i = idx; i < n; i++) {
            swap(nums[idx], nums[i]);
            generate_permutations(ans, nums, idx + 1, n);
            swap(nums[idx], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        generate_permutations(ans, nums, 0, n);
        return ans;
    }
};
