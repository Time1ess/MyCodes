struct pair_hash {
    inline std::size_t operator()(const pair<int, int>& p) const {
        return p.first * 10000 + p.second;
    }  
};
class Solution {
public:
    /**
     * @param matrix: a 0-1 matrix
     * @return: return a matrix
     */
    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix) {
        // write your code here
        int n = matrix.size();
        if(n == 0) {
            return {};
        }
        int m = matrix[0].size();
        if(m == 0) {
            return {};
        }
        vector<vector<int>> ans(n, vector<int>(m, -1));
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(matrix[i][j] == 0) {
                    ans[i][j] = 0;
                } else {
                    unordered_set<pair<int, int>, pair_hash> visited;
                    queue<pair<int, int>> q;
                    visited.insert({i, j});
                    q.push({i, j});
                    while(!q.empty()) {
                        auto front = q.front();
                        q.pop();
                        int x = front.first;
                        int y = front.second;
                        if(matrix[x][y] == 0) {
                            ans[i][j] = abs(i-x) + abs(j-y);
                            break;
                        }
                        static const vector<pair<int, int>> directions = {
                            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
                        };
                        for(auto dir: directions) {
                            int next_x = x + dir.first;
                            int next_y = y + dir.second;
                            if(next_x >= 0 && next_x < n
                               && next_y >= 0 && next_y < m
                               && visited.find({next_x, next_y}) == visited.end()) {
                                visited.insert({next_x, next_y});
                                q.push({next_x, next_y});
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};
