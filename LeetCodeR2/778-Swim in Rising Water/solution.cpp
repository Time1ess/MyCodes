class Solution {
public:
    void dfs(vector<vector<int>> &grid, vector<vector<int>> &mem, int n, int i, int j, int current)
    {
        static const vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        if(i < 0 || i == n || j < 0 || j == n || mem[i][j] <= current)
            return;
        mem[i][j] = max(current, grid[i][j]);
        for(auto d: directions)
            dfs(grid, mem, n, i + d.first, j + d.second, mem[i][j]);
    }
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n == 0)
            return 0;
        vector<vector<int>> mem(n, vector<int>(n, INT_MAX));
        dfs(grid, mem, n, 0, 0, 0);
        return mem[n-1][n-1];
    }
};
