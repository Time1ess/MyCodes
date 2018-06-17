class Transform {
public:
    void horizontalFlip(vector<vector<int>>& mat, int n) {
        for(int r1 = 0; r1 < n / 2; r1++) {
            int r2 = n - r1 - 1;
            for(int j = 0; j < n; j++)
                swap(mat[r1][j], mat[r2][j]);
        }
    }
    void diagFlip(vector<vector<int>>& mat, int n) {
        for(int i = 0; i < n; i++) {
            int x1 = i, y1 = 0;
            int x2 = 0, y2 = i;
            while(x2 < x1 && y1 < y2)
                swap(mat[x1--][y1++], mat[x2++][y2--]);
        }
        for(int j = 1; j < n; j++) {
            int x1 = n - 1, y1 = j;
            int x2 = j, y2 = n - 1;
            while(x2 < x1 && y1 < y2)
                swap(mat[x1--][y1++], mat[x2++][y2--]);
        }
    }
    vector<vector<int> > transformImage(vector<vector<int> > mat, int n) {
        // write code here
        horizontalFlip(mat, n);
        diagFlip(mat, n);
        return mat;
    }
};
