class Solution {
public:
    /**
     * @param matrix: the given matrix
     * @return: The list of grid coordinates
     */
    void dfs(vector<vector<int>>& matrix, vector<vector<int>>& ans,
             vector<vector<int>>& visited, int x, int y, int n, int m,
             int pre_val, int dir) {
        if(x < 0 || x == m || y < 0 || y == n || matrix[x][y] < pre_val ||
           (visited[x][y] & dir) == dir) {
            return;       
        }
        visited[x][y] |= dir;
        if(visited[x][y] == 3) {
            ans.push_back({x, y});
        }
        dfs(matrix, ans, visited, x, y-1, n, m, matrix[x][y], visited[x][y]);
        dfs(matrix, ans, visited, x, y+1, n, m, matrix[x][y], visited[x][y]);
        dfs(matrix, ans, visited, x-1, y, n, m, matrix[x][y], visited[x][y]);
        dfs(matrix, ans, visited, x+1, y, n, m, matrix[x][y], visited[x][y]);
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix) {
        // write your code here
        int m = matrix.size();
        if(m == 0) {
            return {};
        }
        int n = matrix[0].size();
        if(n == 0) {
            return {};
        }
        vector<vector<int>> ans;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        for(int i = 0; i < m; i++) {
            dfs(matrix, ans, visited, i, 0, n, m, INT_MIN, 1);
            dfs(matrix, ans, visited, i, n-1, n, m, INT_MIN, 2);
        }
        for(int j = 0; j < n; j++) {
            dfs(matrix, ans, visited, 0, j, n, m, INT_MIN, 1);
            dfs(matrix, ans, visited, m-1, j, n, m, INT_MIN, 2);
        }
        return ans;
    }
};
