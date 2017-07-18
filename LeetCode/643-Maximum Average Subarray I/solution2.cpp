// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-18 08:37
// Last modified: 2017-07-18 08:37
// Filename: solution2.cpp
// Description:
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double slide_sum = 0;
        int j = 0;
        int size = nums.size();
        for(;j < k; j++)
            slide_sum += nums[j];
        double ans = slide_sum;
        while(j < size)
        {
            slide_sum = slide_sum - nums[j-k] + nums[j];
            ans = max(ans, slide_sum);
            j++;
        }
        return ans / k;
    }
};
