class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
            return 0;
        int mmax, second_mmax, idx;
        mmax = second_mmax = INT_MIN;
        for(int i = 0; i < n; i++)
        {
            if(nums[i] > mmax)
            {
                idx = i;
                second_mmax = mmax;
                mmax = nums[i];
            }
            else if(nums[i] > second_mmax)
            {
                second_mmax = nums[i];
            }
        }
        if(mmax >= second_mmax * 2)
            return idx;
        else
            return -1;
    }
};
