class Solution {
public:
    /**
     * @param nums: an array
     * @param k: an integer
     * @return: the maximum average value
     */
    double findMaxAverage(vector<int> &nums, int k) {
        // Write your code here
        int max_sum = 0, cur_sum = 0;
        int n = nums.size();
        for(int i = 0; i < k; i++)
            cur_sum += nums[i];
        max_sum = cur_sum;
        for(int i = k; i < n; i++)
        {
            cur_sum = cur_sum - nums[i-k] + nums[i];
            max_sum = max(max_sum, cur_sum);
        }
        return 1.0 * max_sum / k;
    }
};
