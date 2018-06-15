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
        vector<int> maxs(n, 0);
        int tmax = INT_MIN;
        for(int i = 0; i < n; i++) {
            maxs[i] = tmax;
            tmax = max(tmax, nums[i]);
        }
        vector<int> mins(n, 0);
        int tmin = INT_MAX;
        for(int i = n - 1; i >= 0; i--) {
            mins[i] = tmin;
            tmin = min(tmin, nums[i]);
        }
        int left = 0, right = n - 1;
        while(left < right && maxs[left] <= nums[left] && mins[left] >= nums[left])
            left++;
        while(left < right && maxs[right] <= nums[right] && mins[right] >= nums[right])
            right--;
        return right == left ? 0 : right - left + 1;
    }
};
