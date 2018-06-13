class Solution {
public:
    /**
     * @param grid: a 2D array
     * @return: the perimeter of the island
     */
    int perimeter(const vector<vector<int>>& grid, int m, int n, int x, int y) {
        if (grid[x][y] == 0)
            return 0;
        int ans = 0;
        if (x == 0 || grid[x-1][y] == 0)
            ans++;
        if (x == m - 1 || grid[x+1][y] == 0)
            ans++;
        if (y == 0 || grid[x][y-1] == 0)
            ans++;
        if (y == n - 1 || grid[x][y+1] == 0)
            ans++;
        return ans;
    }
    int islandPerimeter(vector<vector<int>> &grid) {
        // Write your code here
        int m = grid.size();
        if (m == 0)
            return 0;
        int n = grid[0].size();
        if (n == 0)
            return 0;
        int ans = 0;
        for (int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                ans += perimeter(grid, m, n, i, j);
        return ans;
    }
};
