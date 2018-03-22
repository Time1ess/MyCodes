class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)
            return -1;
        vector<int> prefix_sum(n+1, 0), suffix_sum(n+1, 0);
        prefix_sum[0] = nums[0];
        for(int i = 1; i < n; i++)
            prefix_sum[i] = prefix_sum[i-1] + nums[i];
        suffix_sum[n-1] = nums[n-1];
        for(int i = n - 2; i >= 0; i--)
            suffix_sum[i] = suffix_sum[i+1] + nums[i];
        for(int i = 0; i < n; i++)
            if((i == 0 ? 0 : prefix_sum[i-1]) == (i == n - 1 ? 0 : suffix_sum[i+1]))
                return i;
        return -1;
    }
};
