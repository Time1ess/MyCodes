// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-04 09:10
// Last modified: 2017-05-04 09:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    int DFS(vector<vector<int>> &matrix, vector<vector<int>> &mem, int &m, int &n, int x, int y)
    {
        if(mem[x][y] != 0)
            return mem[x][y];
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int longest = 1;
        for(int i = 0; i < 4; i++)
        {
            int nextx = dirs[i][0] + x;
            int nexty = dirs[i][1] + y;
            if(nextx >= 0 && nextx < m && nexty >= 0 && nexty < n && matrix[nextx][nexty] > matrix[x][y])
                longest = max(longest, 1 + DFS(matrix, mem, m, n, nextx, nexty));
        }
        mem[x][y] = longest;
        return longest;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0)
            return 0;
        int n = matrix[0].size();
        int longest = 0;
        vector<vector<int>> mem(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                longest = max(longest, DFS(matrix, mem, m, n, i, j));
        return longest;
    }
};
