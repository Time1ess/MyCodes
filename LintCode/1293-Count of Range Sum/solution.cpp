class Solution {
public:
    /**
     * @param nums: a list of integers
     * @param lower: a integer
     * @param upper: a integer
     * @return: return a integer
     */
    int countRangeSum(vector<int> &nums, int lower, int upper) {
        // write your code here
        unordered_map<int, int> sums_cnt;
        int sum = 0;
        int cnt = 0;
        int n = nums.size();
        sums_cnt[0] = 1;
        for(int i = 0; i < n; i++) {
            sum += nums[i];
            // lower <= sum - x <= upper
            for(int x = sum - upper; x <= sum - lower; x++) {
                cnt += sums_cnt[x];
            }
            sums_cnt[sum]++;
        }
        return cnt;
    }
};
