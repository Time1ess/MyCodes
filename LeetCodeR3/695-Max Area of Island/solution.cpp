class Solution {
public:
    int dfs(vector<vector<int>>& grid, int i, int j, int m, int n) {
        if (i < 0 || i == m || j < 0 || j == n || grid[i][j] == 0) {
            return 0;
        }
        grid[i][j] = 0;
        return 1
            + dfs(grid, i - 1, j, m, n)
            + dfs(grid, i + 1, j, m, n)
            + dfs(grid, i, j - 1, m, n)
            + dfs(grid, i, j + 1, m, n);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();
        if (n == 0) {
            return 0;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, dfs(grid, i, j, m, n));
            }
        }
        return ans;
    }
};
