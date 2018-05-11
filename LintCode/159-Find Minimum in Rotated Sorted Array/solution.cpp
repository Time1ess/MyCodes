class Solution {
public:
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    int findMin(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        int l = 0, r = n - 1;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[l] < nums[r])
                r = m - 1;
            else
                if(nums[m] >= nums[l])
                    l = m + 1;
                else
                    r = m;
        }
        return nums[l];
    }
};
