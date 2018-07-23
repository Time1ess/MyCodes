class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: whether the ball could stop at the destination
     */
    bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited,
             vector<int> current, const vector<int>& destination, int n, int m) {
        int x = current[0];
        int y = current[1];
        if(x == destination[0] && y == destination[1]) {
            return true;
        }
        if(visited[x][y]) {
            return false;
        }
        visited[x][y] = true;
        bool can_reach = false;
        int tx, ty;
        tx = x;
        ty = y;
        // Up
        while(tx > 0 && maze[tx-1][ty] == 0) {
            tx--;
        }
        can_reach = can_reach || dfs(maze, visited, {tx, ty}, destination, n, m);
        // Down
        tx = x;
        ty = y;
        while(tx < n - 1 && maze[tx+1][ty] == 0) {
            tx++;
        }
        can_reach = can_reach || dfs(maze, visited, {tx, ty}, destination, n, m);
        // Left
        tx = x;
        ty = y;
        while(ty > 0 && maze[tx][ty-1] == 0) {
            ty--;
        }
        can_reach = can_reach || dfs(maze, visited, {tx, ty}, destination, n, m);
        // Right
        tx = x;
        ty = y;
        while(ty < m - 1 && maze[tx][ty+1] == 0) {
            ty++;
        }
        can_reach = can_reach || dfs(maze, visited, {tx, ty}, destination, n, m);
        return can_reach;
    }
    bool hasPath(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination) {
        // write your code here
        int n = maze.size();
        if(n == 0) {
            return false;
        }
        int m = maze[0].size();
        if(m == 0) {
            return false;
        }
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        if(dfs(maze, visited, start, destination, n, m)) {
            return true;
        }
        return false;
    }
};
