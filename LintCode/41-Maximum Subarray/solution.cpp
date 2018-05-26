class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> &nums) {
        // write your code here
        int cur = INT_MIN, ans = INT_MIN;
        for(auto x: nums) {
            if(cur < 0)
                cur = x;
            else
                cur += x;
            ans = max(cur, ans);
        }
        return ans;
    }
};
