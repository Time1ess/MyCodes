class Solution {
public:
    /*
     * @param nums: A set of numbers
     * @return: A list of lists
     */
    void dfs(vector<int> &nums, vector<vector<int>> &ans, vector<int> &current, int idx)
    {
        if(idx == nums.size())
        {
            ans.push_back(current);
            return;
        }
        while(idx < nums.size() - 1 && nums[idx] == nums[idx+1])
            idx++;
        dfs(nums, ans, current, idx+1);
        current.push_back(nums[idx]);
        dfs(nums, ans, current, idx+1);
        current.pop_back();
    }
    vector<vector<int>> subsets(vector<int> &nums) {
        // write your code here
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> current;
        dfs(nums, ans, current, 0);
        return ans;
    }
};
