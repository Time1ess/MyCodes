class Solution {
public:
    /**
     * @param nums: the given array
     * @param s: the given target
     * @return: the number of ways to assign symbols to make sum of integers equal to target S
     */
    void dfs(vector<int>& nums, int& cnt, int idx, int n, int cur) {
        if(idx == n) {
            if(cur == 0)
                cnt++;
            return;
        }
        dfs(nums, cnt, idx+1, n, cur+nums[idx]);
        dfs(nums, cnt, idx+1, n, cur-nums[idx]);
    }
    int findTargetSumWays(vector<int> &nums, int s) {
        // Write your code here
        int cnt = 0;
        int n = nums.size();
        dfs(nums, cnt, 0, n, s);
        return cnt;
    }
};
