class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1)
            return 0;
        int mmin = nums[n-1], mmax = nums[0];
        int s = n, e = 0;
        for(int i = 0; i < n; i++)
        {
            mmax = max(mmax, nums[i]);
            mmin = min(mmin, nums[n - 1 - i]);
            if(nums[i] < mmax)
                e = i;
            if(nums[n - 1 - i] > mmin)
                s = n - 1 - i;
        }
        if(s >= e)
            return 0;
        return e - s + 1;
    }
};
