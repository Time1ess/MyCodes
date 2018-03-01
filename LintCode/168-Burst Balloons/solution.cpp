class Solution {
public:
    /**
     * @param nums: A list of integer
     * @return: An integer, maximum coins
     */
    int max_coins(vector<vector<int>> &dp, vector<int> &nums, int l, int r)
    {
        if(dp[l][r] != 0)
            return dp[l][r];
        if(l + 1 == r)
            return 0;
        int ans = 0;
        for(int i = l + 1; i < r; i++)
        {
            int burst = nums[l] * nums[i] * nums[r];
            int left = max_coins(dp, nums, l, i);
            int right = max_coins(dp, nums, i, r);
            ans = max(ans, burst + left + right);
        }
        dp[l][r] = ans;
        return ans;
    }
    int maxCoins(vector<int> &nums) {
        // write your code here
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        if(n == 2)
            return 0;
        else if(n == 3)
            return nums[1];
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = 0;
        for(int i = 1; i < n - 1; i++)
        {
            int burst = nums[0] * nums[i] * nums[n-1];
            int left = max_coins(dp, nums, 0, i);
            int right = max_coins(dp, nums, i, n - 1);
            ans = max(ans, burst + left + right);
        }
        return ans;
    }
};
