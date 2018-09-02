class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> sum_indices;
        int cur = 0;
        int ans = 0;
        sum_indices[0] = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                cur--;
            } else {
                cur++;
            }
            if (sum_indices.find(cur) != sum_indices.end()) {
                ans = max(ans, i - sum_indices[cur]);
            } else {
                sum_indices[cur] = i;
            }
        }
        return ans;
    }
};
