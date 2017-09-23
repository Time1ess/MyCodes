// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-23 09:35
// Last modified: 2017-09-23 09:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> paths_num(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i == 0 && j == 0 && obstacleGrid[i][j] != 1)
                    paths_num[i][j] = 1;
                else if(i == 0 && j != 0 && obstacleGrid[i][j] != 1)
                    paths_num[i][j] = paths_num[i][j-1];
                else if(i != 0 && j == 0 && obstacleGrid[i][j] != 1)
                    paths_num[i][j] = paths_num[i-1][j];
                else if(obstacleGrid[i][j] != 1)
                    paths_num[i][j] = paths_num[i-1][j] + paths_num[i][j-1];
            }
        }
        return paths_num[m-1][n-1];
    }
};
