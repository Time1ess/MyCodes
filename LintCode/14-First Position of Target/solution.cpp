class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    int binarySearch(vector<int> &nums, int target) {
        // write your code here
        int n = nums.size();
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[m] < target)
                l = m + 1;
            else
                r = m;
        }
        if(l < n && nums[l] == target)
            return l;
        else
            return -1;
    }
};
