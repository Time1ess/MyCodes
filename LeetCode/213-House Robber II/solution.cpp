// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-01 09:15
// Last modified: 2017-08-01 09:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if(size == 0)
            return 0;
        else if(size == 1)
            return nums[0];
        else if(size == 2)
            return max(nums[0], nums[1]);
        int dp[size+1][2] = {{0}};
        dp[0][1] = nums[0];
        dp[1][1] = nums[0];
        dp[1][0] = nums[1];
        for(int i = 2; i < size - 1; i++)
        {
            //Max profit include robbing house 1
            dp[i][1] = max(dp[i-1][1], dp[i-2][1] + nums[i]);
            //Max profit exclude robbing house 1
            dp[i][0] = max(dp[i-1][0], dp[i-2][0] + nums[i]);
        }
        int mp_i1, mp_e1;
        mp_i1 = max(dp[size-2][1], dp[size-3][1]); // Cannot robbing last house cause house 1 was robbed
        mp_e1 = max(dp[size-2][0], dp[size-3][0] + nums[size-1]);
        return max(mp_i1, mp_e1);
    }
};
