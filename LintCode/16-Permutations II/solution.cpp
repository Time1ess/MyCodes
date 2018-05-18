class Solution {
public:
    /*
     * @param :  A list of integers
     * @return: A list of unique permutations
     */
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        queue<pair<vector<int>, int>> q;
        q.push({nums, 0});
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
                swap(tmp_nums[i], tmp_nums[x.second]);
                while(i + 1 < n && tmp_nums[x.second] == tmp_nums[i+1])
                    i++;
                sort(tmp_nums.begin() + x.second + 1, tmp_nums.end());
                q.push({tmp_nums, x.second+1});
            }
        }
        return ans;
    }
};
