class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str, int x, int y, vector<vector<bool>> &visited)
    {
        if(str && *str == '\0')
            return true;
        if(!str
           || x < 0 || x >= rows
           || y < 0 || y >= cols
           || visited[x][y]
           || matrix[x * cols + y] != *str)
            return false;
        visited[x][y] = true;
        bool found = false;
        found = hasPath(matrix, rows, cols, str+1, x-1, y, visited)
            || hasPath(matrix, rows, cols, str+1, x+1, y, visited)
            || hasPath(matrix, rows, cols, str+1, x, y-1, visited)
            || hasPath(matrix, rows, cols, str+1, x, y+1, visited);
        if(found)
            return true;
        visited[x][y] = false;
        return false;
    }
        
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
    	if(!matrix || rows <= 0 || cols <= 0)
            return false;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                if(hasPath(matrix, rows, cols, str, i, j, visited))
                    return true;
        return false;
    }
};
