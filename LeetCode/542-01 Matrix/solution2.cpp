// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-30 11:23
// Last modified: 2017-08-30 11:23
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 1e6));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            {
                if(matrix[i][j] == 0)
                {
                    ans[i][j] = 0;
                    continue;
                }
                if(i > 0)
                    ans[i][j] = min(ans[i][j], ans[i-1][j]+1);
                if(j > 0)
                    ans[i][j] = min(ans[i][j], ans[i][j-1]+1);
            }
        for(int i = m-1; i >= 0; i--)
            for(int j = n-1; j >= 0; j--)
            {
                if(ans[i][j] == 0)
                    continue;
                if(i < m-1)
                    ans[i][j] = min(ans[i][j], ans[i+1][j]+1);
                if(j < n-1)
                    ans[i][j] = min(ans[i][j], ans[i][j+1]+1);
            }
        return ans;
    }
};
