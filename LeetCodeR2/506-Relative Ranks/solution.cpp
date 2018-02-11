bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first > b.first;
}
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> score_indices;
        for(int i = 0; i < n; i++)
            score_indices.push_back({nums[i], i});
        sort(score_indices.begin(), score_indices.end(), cmp);
        // High -> Low
        vector<string> ans(n, "");
        for(int i = 0; i < n; i++)
        {
            auto p = score_indices[i];
            if(i == 0)
                ans[p.second] = "Gold Medal";
            else if(i == 1)
                ans[p.second] = "Silver Medal";
            else if(i == 2)
                ans[p.second] = "Bronze Medal";
            else
                ans[p.second] = to_string(i+1);
        }
        return ans;
    }
};
