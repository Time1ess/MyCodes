bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first;
}
class Solution {
public:
    /**
     * @param nums: List[int]
     * @return: return List[str]
     */
    vector<string> findRelativeRanks(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        vector<pair<int, int>> indices;
        for(int i = 0; i < n; i++) {
            indices.push_back({nums[i], i});
        }
        sort(indices.begin(), indices.end(), cmp);
        vector<string> ans(n, "");
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                ans[indices[i].second] = "Gold Medal";
            } else if(i == 1) {
                ans[indices[i].second] = "Silver Medal";
            } else if(i == 2) {
                ans[indices[i].second] = "Bronze Medal";
            } else {
                ans[indices[i].second] = to_string(i+1);
            }
        }
        return ans;
    }
};
