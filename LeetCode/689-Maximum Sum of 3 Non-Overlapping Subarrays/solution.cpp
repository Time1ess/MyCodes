// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-04 09:55
// Last modified: 2017-10-04 09:55
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int size = nums.size();
        vector<int> left(size, 0), right(size, size - k), ans(3, 0), prefix_sum = {0};
        for(auto x: nums)
            prefix_sum.push_back(prefix_sum.back() + x);
        for(int i = k, max_sum = prefix_sum[k]; i < size; i++)
        {
            if(prefix_sum[i+1] - prefix_sum[i+1-k] > max_sum)
            {
                max_sum = prefix_sum[i+1] - prefix_sum[i+1-k];
                left[i] = i + 1 - k;
            }
            else
                left[i] = left[i-1];
        }
        for(int i = size - k - 1, max_sum = prefix_sum[size] - prefix_sum[size-k]; i >= 0; i--)
        {
            if(prefix_sum[i+k] - prefix_sum[i] >= max_sum)
            {
                max_sum = prefix_sum[i+k] - prefix_sum[i];
                right[i] = i;
            }
            else
                right[i] = right[i+1];
        }
        int max_sum = 0;
        for(int m = k; m <= size - 2 * k; m++)
        {
            int l = left[m-1], r = right[m+k];
            int tmp = prefix_sum[l+k] - prefix_sum[l] + prefix_sum[m+k] - prefix_sum[m] + prefix_sum[r+k] - prefix_sum[r];
            if(tmp > max_sum)
            {
                max_sum = tmp;
                ans = {l, m, r};
            }
        }
        return ans;
    }
};
