// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-05 10:40
// Last modified: 2017-08-05 10:40
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int max_row = triangle.size();
        if(max_row == 0)
            return 0;
        vector<int> minimums = triangle[max_row-1];
        for(int row = max_row-2; row >= 0; row--)
            for(int col = 0; col < triangle[row].size(); col++)
                minimums[col] = triangle[row][col] + min(minimums[col], minimums[col+1]);
        return minimums[0];
    }
};
