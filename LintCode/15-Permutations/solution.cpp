class Solution {
public:
    /*
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    vector<vector<int>> permute(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        sort(nums.begin(), nums.end());
        queue<pair<vector<int>, int>> q;
        q.push({nums, 0});
        vector<vector<int>> ans;
        while(!q.empty())
        {
            auto x = q.front();
            q.pop();
            if(x.second == n)
            {
                ans.push_back(x.first);
                continue;
            }
            for(int i = x.second; i < n; i++)
            {
                vector<int> tmp_nums = x.first;
                swap(tmp_nums[x.second], tmp_nums[i]);
                q.push({tmp_nums, x.second + 1});
            }
        }
        return ans;
    }
};
