class Solution {
public:
    void dfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();
        if(i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] == '0')
            return;
        visited[i][j] = true;
        dfs(grid, visited, i-1, j);
        dfs(grid, visited, i+1, j);
        dfs(grid, visited, i, j-1);
        dfs(grid, visited, i, j+1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if(m == 0)
            return 0;
        int n = grid[0].size();
        if(n == 0)
            return 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int ans = 0;
        for(int i = 0;i < m; i++)
            for(int j = 0; j < n; j++)
                if(visited[i][j] == false && grid[i][j] == '1')
                {
                    ans++;
                    dfs(grid, visited, i, j);
                }
        return ans;
    }
};
