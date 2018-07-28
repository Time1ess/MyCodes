class Solution {
public:
    /*
     * @param nums: a set of distinct positive integers
     * @return: the largest subset 
     */
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> dp(n, 0);
        int max_idx = 0;
        for(int i = 1; i < n; i++) {
            for(int j = i; j >= 0; j--) {
                if(nums[i] % nums[j] == 0) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            if(dp[max_idx] < dp[i]) {
                max_idx = i;
            }
        }
        vector<int> ans;
        int cnt = dp[max_idx];
        int devide_end = nums[max_idx];
        for(int i = max_idx; i >= 0; i--) {
            if(devide_end % nums[i] == 0 && dp[i] == cnt) {
                ans.push_back(nums[i]);
                devide_end = nums[i];
                cnt--;
            }
        }
        return ans;
    }
};
