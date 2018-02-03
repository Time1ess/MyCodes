class Solution {
public:
    /*
     * @param : the given array
     * @return: the minimum difference between their sums 
     */
    int findMin(vector<int> &nums) {
        // write your code here
        int size = nums.size();
        if(size == 0)
            return 0;
        else if(size == 1)
            return nums[0];

        int sum = 0;
        for(auto x: nums)
            sum += x;
        vector<int> dp(sum / 2 + 1, 0);
        for(int i = 0; i < size; i++)
            for(int j = sum / 2; j >= nums[i]; j--)
                dp[j] = dp[j - nums[i]] + nums[i] > dp[j] ? dp[j-nums[i]]+nums[i]:dp[j];
        return abs(sum - 2 * dp[sum / 2]);
    }
};
