class Solution {
public:
    void mark_islands(vector<vector<int>> &grid, vector<vector<int>> &belong,
                      const int n, const int m, int i, int j, int &island, int &size)
    {
        if(i < 0 || i == n || j < 0 || j == m || grid[i][j] == 0 || belong[i][j] != -1)
            return;
        belong[i][j] = island;
        size++;
        mark_islands(grid, belong, n, m, i, j - 1, island, size);
        mark_islands(grid, belong, n, m, i, j + 1, island, size);
        mark_islands(grid, belong, n, m, i - 1, j, island, size);
        mark_islands(grid, belong, n, m, i + 1, j, island, size);
    }
    int merge_island(vector<vector<int>> &grid, vector<vector<int>> &belong,
                     unordered_map<int, int> &island_size, const int n, const int m,
                     int i, int j)
    {
        if(grid[i][j] == 1)
            return island_size[belong[i][j]];
        vector<int> sizes;
        unordered_set<int> belongs;
        if(i > 0 && grid[i-1][j] != 0 && belongs.find(belong[i-1][j]) == belongs.end())
        {
            sizes.push_back(island_size[belong[i-1][j]]);
            belongs.insert(belong[i-1][j]);
        }
        if(i < n - 1 && grid[i+1][j] != 0 && belongs.find(belong[i+1][j]) == belongs.end())
        {
            sizes.push_back(island_size[belong[i+1][j]]);
            belongs.insert(belong[i+1][j]);
        }
        if(j > 0 && grid[i][j-1] != 0 && belongs.find(belong[i][j-1]) == belongs.end())
        {
            sizes.push_back(island_size[belong[i][j-1]]);
            belongs.insert(belong[i][j-1]);
        }
        if(j < m - 1 && grid[i][j+1] != 0 && belongs.find(belong[i][j+1]) == belongs.end())
        {
            sizes.push_back(island_size[belong[i][j+1]]);
            belongs.insert(belong[i][j+1]);
        }
        return accumulate(sizes.begin(), sizes.end(), 1);
    }
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> belong(n, vector<int>(m, -1));
        int island = 0;
        unordered_map<int, int> island_size;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(grid[i][j] == 1 && belong[i][j] == -1)
                {
                    int size = 0;
                    mark_islands(grid, belong, n, m, i, j, island, size);
                    island_size[island] = size;
                    island++;
                }
        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans = max(ans, merge_island(grid, belong, island_size, n, m, i, j));
        return ans;
    }
};
