class Solution {
public:
    void gen_permutations(vector<vector<int>> &ans, vector<int> &nums, int idx, int n)
    {
        if(idx == n)
        {
            ans.push_back(nums);
            return;
        }
        for(int i = idx; i < n; i++)
        {
            swap(nums[idx], nums[i]);
            gen_permutations(ans, nums, idx + 1, n);
            swap(nums[idx], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        gen_permutations(ans, nums, 0, n);
        return ans;
    }
};
