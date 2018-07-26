class Solution {
public:
    /**
     * @param nums: nums an array of scores
     * @return: check if player 1 will win
     */
    bool PredictTheWinner(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
        }
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                // nums[i], nums[i+1], ..., nums[j]
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
            }
        }
        return dp[0][n-1] >= 0;
    }
};
