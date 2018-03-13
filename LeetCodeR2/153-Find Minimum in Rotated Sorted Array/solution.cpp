class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while(l < r)
        {
            if(nums[l] < nums[r])
                return nums[l];
            int m = l + (r - l) / 2;
            if(nums[m] >= nums[l])
                l = m + 1;
            else
                r = m;
        }
        return nums[l];
    }
};
