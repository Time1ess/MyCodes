class Solution {
public:
    /**
     * @param nums: an array
     * @return: the shortest subarray's length
     */
    int findUnsortedSubarray(vector<int> &nums) {
        // Write your code here
        int n = nums.size();
        if(n == 0)
            return 0;
        int tmax = INT_MIN, tmin = INT_MAX;
        int start = -1, end = -2;
        for(int i = 0; i < n; i++) {
            tmax = max(tmax, nums[i]);
            if(nums[i] < tmax)
                end = i;
            tmin = min(tmin, nums[n-i-1]);
            if(nums[n-i-1] > tmin)
                start = n - i - 1;
        }
        return end - start + 1;
    }
};
