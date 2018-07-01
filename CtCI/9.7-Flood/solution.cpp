class Flood {
public:
    int floodFill(vector<vector<int> > map, int n, int m) {
        // write code here
        queue<pair<pair<int, int>, int>> q;
        static const vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        q.push({{0, 0}, 0});
        map[0][0] = 1;
        while(!q.empty()) {
            auto front = q.front();
            auto pos = front.first;
            int time = front.second;
            q.pop();
            if(pos.first == n - 1 && pos.second == m - 1)
                return time;
            for(auto dir: dirs) {
                int x = pos.first + dir.first;
                int y = pos.second + dir.second;
                if(x < 0 || x >= n || y < 0 || y >= m || map[x][y] == 1)
                    continue;
                q.push({{x, y}, time+1});
                map[x][y] = 1;
            }
        }
        return -1;
    }
};
