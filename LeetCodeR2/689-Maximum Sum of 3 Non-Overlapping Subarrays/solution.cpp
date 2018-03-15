class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        int asum = 0;
        for(int i = 0; i < n; i++)
        {
            asum += nums[i];
            if(i >= k)
                asum -= nums[i-k];
            if(i >= k - 1)
                sum[i-k+1] = asum;
        }
        vector<int> left(n, 0);
        int best = 0;
        for(int i = 0; i < n; i++)
        {
            if(sum[i] > sum[best])
                best = i;
            left[i] = best;
        }
        vector<int> right(n, 0);
        best = n - 1;
        for(int i = n - 1; i >= 0; i--)
        {
            if(sum[i] > sum[best])
                best = i;
            right[i] = best;
        }
        vector<int> ans{-1, -1, -1};
        for(int j = k; j < n - k; j++)
        {
            int l = left[j - k], r = right[j + k];
            if(ans[0] == -1 || (sum[l] + sum[j] + sum[r] > sum[ans[0]] + sum[ans[1]] + sum[ans[2]]))
            {
                ans[0] = l;
                ans[1] = j;
                ans[2] = r;
            }
        }
        return ans;
    }
};
