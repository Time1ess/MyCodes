// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-18 08:27
// Last modified: 2017-07-18 08:27
// Filename: solution.cpp
// Description:
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int size = nums.size();
        long long presum[size+1] = {0};
        int s = 0;
        for(int i = 0; i <= size; i++)
        {
            presum[i] = s;
            if(i == size)
                break;
            s += nums[i];
        }
        double ans = -1e9;
        for(int i = 0; i + k <= size; i++)
            ans = max(ans, 1.0 * (presum[i+k] - presum[i]));
        return ans / k;
    }
};
