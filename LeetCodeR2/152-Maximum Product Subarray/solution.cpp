class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)
            return 0;
        else if(n == 1)
            return nums[0];
        int mmax = nums[0], mmin = nums[0], ans = nums[0];
        for(int i = 1; i < n; i++)
        {
            if(nums[i] < 0)
                swap(mmax, mmin);
            mmax = max(nums[i], mmax * nums[i]);
            mmin = min(nums[i], mmax * nums[i]);

            ans = max(ans, mmax);
        }
        return ans;
    }
};
