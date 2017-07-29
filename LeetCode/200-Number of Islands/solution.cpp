// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-29 11:09
// Last modified: 2017-07-29 11:09
// Filename: solution.cpp
// Description:
class Solution {
public:
    void expand_lands(vector<vector<char>> &grid, int x, int y, int &max_x, int &max_y)
    {
        if(x < 0 || x >= max_x || y < 0 || y >= max_y || grid[x][y] == '0')
            return;
        grid[x][y] = '0';
        expand_lands(grid, x-1, y, max_x, max_y);
        expand_lands(grid, x, y-1, max_x, max_y);
        expand_lands(grid, x+1, y, max_x, max_y);
        expand_lands(grid, x, y+1, max_x, max_y);
    }
    int numIslands(vector<vector<char>>& grid) {
        int max_x = grid.size();
        if(max_x == 0)
            return 0;
        int max_y = grid[0].size();
        int cnt = 0;
        for(int x = 0; x < max_x; x++)
            for(int y = 0; y < max_y; y++)
            {
                if(grid[x][y] == '1')
                {
                    expand_lands(grid, x, y, max_x, max_y);
                    cnt++;
                }
            }
        return cnt;
    }
};
