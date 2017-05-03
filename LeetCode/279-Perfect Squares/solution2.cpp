// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-03 15:50
// Last modified: 2017-05-03 15:52
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int numSquares(int n) {
        static vector<int> dp({0});  // Continue from last n, no waste computation
        while(dp.size() <= n)
        {
            int m = dp.size();
            int min_cnt = INT_MAX;
            for(int i = 1; i * i <= m; i++)
                min_cnt = min(min_cnt, dp[m - i * i] + 1);
            dp.push_back(min_cnt);
        }
        return dp[n];
    }
};
