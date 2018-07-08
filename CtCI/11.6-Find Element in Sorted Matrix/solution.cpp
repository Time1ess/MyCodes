class Finder {
public:
    vector<int> findElement(vector<vector<int> > mat, int n, int m, int tar) {
        // write code here
        int x = 0, y = m - 1;
        while(x < n && y >= 0) {
            if(mat[x][y] == tar)
                return {x, y};
            else if(mat[x][y] > tar)
                y--;
            else
                x++;
        }
        return {-1, -1};
    }
};
