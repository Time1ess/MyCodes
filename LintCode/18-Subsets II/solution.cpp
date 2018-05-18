class Solution {
public:
    /**
     * @param nums: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    void generate_subsets(vector<vector<int>> &ans, vector<int> &current,
                          vector<int> &nums, int idx, int n)
    {
        if(idx == n)
        {
            ans.push_back(current);
            return;
        }
        int next_num_idx = idx + 1;
        while(next_num_idx < n && nums[idx] == nums[next_num_idx])
            next_num_idx++;
        int cnt = next_num_idx - idx;
        for(int i = 0; i < cnt; i++)
            current.push_back(nums[idx]);
        for(int i = 0; i < cnt; i++)
        {
            generate_subsets(ans, current, nums, next_num_idx, n);
            current.pop_back();
        }
        generate_subsets(ans, current, nums, next_num_idx, n);
    }
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        // write your code here
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> current;
        generate_subsets(ans, current, nums, 0, n);
        return ans;
    }
};
