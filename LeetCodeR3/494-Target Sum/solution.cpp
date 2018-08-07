class Solution {
public:
    void backtrack(vector<int>& nums, int& ans, int cur, int idx, int n) {
        if(idx == n) {
            if(cur == 0) {
                ans++;
            }
            return;
        }
        backtrack(nums, ans, cur+nums[idx], idx+1, n);
        backtrack(nums, ans, cur-nums[idx], idx+1, n);
    }
    int findTargetSumWays(vector<int>& nums, int S) {
        int ans = 0;
        backtrack(nums, ans, S, 0, nums.size());
        return ans;
    }
};
