class Solution {
public:
    /*
     * @param grid: a boolean 2D matrix
     * @return: an integer
     */
    void dfs(vector<vector<bool>> &grid, vector<vector<bool>> &visited,
             const int &m, const int &n, int i, int j)
    {
        if(i < 0 || i == m || j < 0 || j == n)
            return;
        if(visited[i][j] || grid[i][j] == false)
            return;
        visited[i][j] = true;
        dfs(grid, visited, m, n, i, j-1);
        dfs(grid, visited, m, n, i, j+1);
        dfs(grid, visited, m, n, i-1, j);
        dfs(grid, visited, m, n, i+1, j);
    }
    int numIslands(vector<vector<bool>> &grid) {
        // write your code here
        int m = grid.size();
        if(m == 0)
            return 0;
        int n = grid[0].size();
        if(n == 0)
            return 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int cnt = 0;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
            if(grid[i][j] == true && visited[i][j] == false)
            {
                cnt++;
                dfs(grid, visited, m, n, i, j);
            }
        return cnt;
    }
};
