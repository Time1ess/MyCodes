// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-08 15:03
// Last modified: 2017-10-08 15:03
// Filename: solution.cpp
// Description:
class Solution {
public:
    int bfs(vector<vector<int>>& grid, int i, int j, int &row, int &col)
    {
        if(i < 0 || i >= row || j < 0 || j >= col || grid[i][j] != 1)
            return 0;
        int area = grid[i][j];
        grid[i][j] = -1;
        area += bfs(grid, i-1, j, row, col);
        area += bfs(grid, i+1, j, row, col);
        area += bfs(grid, i, j-1, row, col);
        area += bfs(grid, i, j+1, row, col);
        return area;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int row = grid.size();
        if(row == 0)
            return 0;
        int col = grid[0].size();
        int max_area = 0;
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                max_area = max(max_area, bfs(grid, i, j, row, col));
        return max_area;
    }
};
