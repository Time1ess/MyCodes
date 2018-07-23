class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: the shortest distance for the ball to stop at the destination
     */
    int shortestDistance(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination) {
        // write your code here
        int n = maze.size();
        if(n == 0) {
            return -1;
        }
        int m = maze[0].size();
        if(m == 0) {
            return -1;
        }
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<vector<int>> q;
        q.push({start[0], start[1], 0});
        visited[start[0]][start[1]] = true;
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            int x = front[0];
            int y = front[1];
            int cost = front[2];
            if(x == destination[0] && y == destination[1]) {
                return cost;
            }
            int tx, ty;
            tx = x;
            ty = y;
            // Up
            while(tx > 0 && maze[tx-1][ty] == 0) {
                tx--;
            }
            if(visited[tx][ty] == false) {
                visited[tx][ty] = true;
                q.push({tx, ty, cost + x - tx});
            }
            // Down
            tx = x;
            ty = y;
            while(tx < n - 1 && maze[tx+1][ty] == 0) {
                tx++;
            }
            if(visited[tx][ty] == false) {
                visited[tx][ty] = true;
                q.push({tx, ty, cost + tx - x});
            }
            // Left
            tx = x;
            ty = y;
            while(ty > 0 && maze[tx][ty-1] == 0) {
                ty--;
            }
            if(visited[tx][ty] == false) {
                visited[tx][ty] = true;
                q.push({tx, ty, cost + y - ty});
            }
            // Right
            tx = x;
            ty = y;
            while(ty < m - 1 && maze[tx][ty+1] == 0) {
                ty++;
            }
            if(visited[tx][ty] == false) {
                visited[tx][ty] = true;
                q.push({tx, ty, cost + ty - y});
            }
        }
        return -1;
    }
};
