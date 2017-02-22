// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-22 09:19
// Last modified: 2017-02-22 09:19
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int size=nums.size();
        int dp[size][size];  // dp[i][j]: how much more a player can gain than the other player
        for(int i=0; i < size; i++)
            dp[i][i] = nums[i];
        for(int len=1; len < size; len++)
            for(int i=0; i < size - len; i++)
            {
                int j = i + len;
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
                // player choose i, leave the other player choose from i+1 to j
                // player choose j, leave the other player choose from i to j-1
                // take the maximum.
            }
        // player 1 can gain more than player 2 from 0 to size-1?
        return dp[0][size-1] >= 0;
    }
};
