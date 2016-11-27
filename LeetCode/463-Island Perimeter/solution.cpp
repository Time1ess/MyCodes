// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-11-27 09:56
// Last modified: 2016-11-27 09:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int ans = 0;
        int size = grid.size();
        for(int i=0; i < size; i++)
        {
            int csize = grid[i].size();
            for(int j=0; j < csize; j++)
            {
                if(grid[i][j]==0)
                    continue;
                ans += 4;
                if(i-1 >= 0)
                    ans -= grid[i-1][j];
                if(i+1 < size)
                    ans -= grid[i+1][j];
                if(j-1 >= 0)
                    ans -= grid[i][j-1];
                if(j+1 < csize)
                    ans -= grid[i][j+1];
            }
        }
        return ans;
    }
};
