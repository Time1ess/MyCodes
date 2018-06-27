class Solution {
public:
    /**
     * @param matrix : the martix
     * @return: the distance of grid to the police
     */
    void pushNearByPositions(queue<pair<pair<int, int>, int>>& q,
                             set<pair<int, int>>& visited,
                             vector<vector<int>>& matrix,
                             int i, int j, int d, int m, int n) {
        if(i > 0 && matrix[i-1][j] != -1 && visited.find({i-1, j}) == visited.end())
            q.push({{i-1, j}, d});
        if(i < m - 1 && matrix[i+1][j] != -1 && visited.find({i+1, j}) == visited.end())
            q.push({{i+1, j}, d});
        if(j > 0 && matrix[i][j-1] != -1 && visited.find({i, j-1}) == visited.end())
            q.push({{i, j-1}, d});
        if(j < n - 1 && matrix[i][j+1] != -1 && visited.find({i, j+1}) == visited.end())
            q.push({{i, j+1}, d});                  
    }
    vector<vector<int>> policeDistance(vector<vector<int>> &matrix ) {
        // Write your code here
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();
        if (n == 0) {
            return {};
        }
        vector<vector<int>> ans(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1)
                    continue;
                else if(matrix[i][j] == 1) {
                    ans[i][j] = 0;
                    continue;
                }
                set<pair<int, int>> visited;
                queue<pair<pair<int, int>, int>> q;
                visited.insert({i, j});
                pushNearByPositions(q, visited, matrix, i, j, 1, m, n);
                while(!q.empty()) {
                    auto p = q.front();
                    q.pop();
                    int x = p.first.first;
                    int y = p.first.second;
                    int d = p.second;
                    visited.insert({x, y});
                    if(matrix[x][y] == 1) {
                        ans[i][j] = d;
                        break;
                    }
                    pushNearByPositions(q, visited, matrix, x, y, d+1, m, n);
                }
            }
        }
        return ans;
    }
};
