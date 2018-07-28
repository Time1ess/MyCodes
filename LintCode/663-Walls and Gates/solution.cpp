class Solution {
public:
    /**
     * @param rooms: m x n 2D grid
     * @return: nothing
     */
    void wallsAndGates(vector<vector<int>> &rooms) {
        // write your code here
        int m = rooms.size();
        if(m == 0) {
            return;
        }
        int n = rooms[0].size();
        if(n == 0) {
            return;
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(rooms[i][j] != INT_MAX) {
                    continue;
                }
                set<vector<int>> visited;
                queue<vector<int>> q;
                q.push({i, j, 0});
                visited.insert({i, j});
                while(!q.empty()) {
                    auto v = q.front();
                    int x = v[0];
                    int y = v[1];
                    int dist = v[2];
                    q.pop();
                    if(rooms[x][y] == 0) {
                        rooms[i][j] = dist;
                        break;
                    }
                    static const vector<vector<int>> directions = 
                        {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
                    for(auto dir: directions) {
                        int next_x = x + dir[0];
                        int next_y = y + dir[1];
                        if(next_x < 0 || next_x >= m
                           || next_y < 0 || next_y >= n
                           || rooms[next_x][next_y] == -1
                           || visited.find({next_x, next_y}) != visited.end()) {
                            continue;
                        }
                        q.push({next_x, next_y, dist + 1});
                        visited.insert({next_x, next_y});
                    }
                }
            }
        }
    }
};
