class Solution {
public:
    int digits_sum(int x, int y)
    {
        int s = 0;
        while(x)
        {
            s += (x % 10);
            x /= 10;
        }
        while(y)
        {
            s += (y % 10);
            y /= 10;
        }
        return s;
    }
    void dfs(vector<vector<bool>> &visited, int &cnt, int threshold, int rows, int cols, int x, int y)
    {
        if(x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y] || digits_sum(x, y) > threshold)
            return;
        visited[x][y] = true;
        cnt++;
        dfs(visited, cnt, threshold, rows, cols, x+1, y);
        dfs(visited, cnt, threshold, rows, cols, x, y+1);
    }
    int movingCount(int threshold, int rows, int cols)
    {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int cnt = 0;
        dfs(visited, cnt, threshold, rows, cols, 0, 0);
        return cnt;
    }
};
