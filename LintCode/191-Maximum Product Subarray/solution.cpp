class Solution {
public:
    /**
     * @param nums: An array of integers
     * @return: An integer
     */
    int maxProduct(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        vector<int> mmax, mmin;
        mmax.push_back(nums[0]);
        mmin.push_back(nums[0]);
        for(int i = 1; i < n; i++) {
            mmax.push_back(max(max(mmax[i-1] * nums[i], mmin[i-1] * nums[i]), nums[i]));
            mmin.push_back(min(min(mmax[i-1] * nums[i], mmin[i-1] * nums[i]), nums[i]));
        }
        int ans = mmax[0];
        for(int i = 1; i < n; i++)
            ans = max(ans, mmax[i]);
        return ans;
    }
};
