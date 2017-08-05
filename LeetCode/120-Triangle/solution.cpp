// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-05 10:12
// Last modified: 2017-08-05 10:12
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int max_row = triangle.size();
        if(max_row == 0)
            return 0;
        else if(max_row == 1)
            return triangle[0][0];
        int max_col = triangle[max_row-1].size();
        int dp[2][max_col+2] = {{0}};
        for(int i = 0; i < max_col+2; i++)
            dp[0][i] = dp[1][i] = 1e9;
        dp[0][1] = triangle[0][0];
        for(int row = 1; row < max_row; row++)
            for(int col = 1; col <= triangle[row].size(); col++)
                dp[row % 2][col] = triangle[row][col-1] + min(dp[(row+1)%2][col-1], dp[(row+1)%2][col]);
        int minimum = 1e9;
        for(int col = 1; col <= max_col; col++)
            minimum = min(minimum, dp[(max_row+1)%2][col]);
        return minimum;
    }
};
