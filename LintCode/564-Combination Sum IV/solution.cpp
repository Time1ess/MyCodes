class Solution {
public:
    /**
     * @param nums: an integer array and all positive numbers, no duplicates
     * @param target: An integer
     * @return: An integer
     */
    int backPackVI(vector<int> &nums, int target) {
        // write your code here
        sort(nums.begin(), nums.end());
        vector<int> dp(target+1, 0);
        dp[0] = 1;
        for(int i = 1; i <= target; i++) {
            for(auto x: nums) {
                if(i - x < 0) {
                    break;
                }
                dp[i] += dp[i-x];
            }
        }
        return dp[target];
    }
};
