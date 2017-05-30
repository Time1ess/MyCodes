// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-23 16:56
// Last modified: 2017-04-23 16:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for(int i = 0; i < nums.size(); i+=2)
            ans += nums[i];
        return ans;
    }
};
