class Solution {
public:
    /**
     * @param nums: The number array
     * @return: Return the single number
     */
    int getSingleNumber(vector<int> &nums) {
        // Write your code here
        int n = nums.size();
        int l = 0, r = n - 1;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(m & 0x1)
            {
                if(nums[m] == nums[m-1])
                    l = m + 1;
                else
                    r = m;
            }
            else
            {
                if(nums[m] == nums[m+1])
                    l = m + 2;
                else
                    r = m;
            }
        }
        return nums[l];
    }
};
