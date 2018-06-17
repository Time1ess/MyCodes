class Solution {
public:
    /**
     * @param grid: Given a 2D grid, each cell is either 'W', 'E' or '0'
     * @return: an integer, the maximum enemies you can kill using one bomb
     */
    int maxKilledEnemies(vector<vector<char>> &grid) {
        // write your code here
        int m = grid.size();
        if(m == 0)
            return 0;
        int n = grid[0].size();
        if(n == 0)
            return 0;
        vector<vector<int>> leftEnemies(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++) {
            int left = 0;
            for(int j = 0; j < n; j++) {
                leftEnemies[i][j] = left;
                if(grid[i][j] == 'W')
                    left = 0;
                else if(grid[i][j] == 'E')
                    left++;
            }
        }
        vector<vector<int>> rightEnemies(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++) {
            int right = 0;
            for(int j = n - 1; j >= 0; j--) {
                rightEnemies[i][j] = right;
                if(grid[i][j] == 'W')
                    right = 0;
                else if(grid[i][j] == 'E')
                    right++;
            }
        }
        vector<vector<int>> topEnemies(m, vector<int>(n, 0));
        for(int j = 0; j < n; j++) {
            int top = 0;
            for(int i = 0; i < m; i++) {
                topEnemies[i][j] = top;
                if(grid[i][j] == 'W')
                    top = 0;
                else if(grid[i][j] == 'E')
                    top++;
            }
        }
        vector<vector<int>> bottomEnemies(m, vector<int>(n, 0));
        for(int j = 0; j < n; j++) {
            int bottom = 0;
            for(int i = m - 1; i >= 0; i--) {
                bottomEnemies[i][j] = bottom;
                if(grid[i][j] == 'W')
                    bottom = 0;
                else if(grid[i][j] == 'E')
                    bottom++;
            }
        }
        int ans = 0;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(grid[i][j] == '0')
                    ans = max(ans,
                              leftEnemies[i][j] + rightEnemies[i][j]
                              + topEnemies[i][j] + bottomEnemies[i][j]);
        return ans;
    }
};
