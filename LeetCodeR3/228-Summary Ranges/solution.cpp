class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return {};
        }
        vector<string> ans;
        int l = nums[0];
        int r = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] != r + 1) {
                if (l == r) {
                    ans.push_back(to_string(l));
                } else {
                    ans.push_back(to_string(l) + "->" + to_string(r));
                }
                l = r = nums[i];
            } else {
                r = nums[i];
            }
        }
        if (l == r) {
            ans.push_back(to_string(l));
        } else {
            ans.push_back(to_string(l) + "->" + to_string(r));
        }
        return ans;
    }
};
