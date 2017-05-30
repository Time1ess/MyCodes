// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-01 12:57
// Last modified: 2017-05-01 12:57
// Filename: solution.cpp
// Description:
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int size = nums.size();
        if(size == 0)
            return 0;
        int pre_sum[size+1] = {0};  // pre_sum[k]: The sum of nums[0...k)
        for(int i = 1; i <= size; i++)
            pre_sum[i] = pre_sum[i-1] + nums[i-1];
        int cnt = 0;
        for(int i = 0; i <= size; i++)
            for(int j = i+1; j <= size; j++)
                if((pre_sum[j] - pre_sum[i]) == k)
                    cnt++;
        return cnt;
    }
};
