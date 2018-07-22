class NumMatrix {
private:
    vector<vector<int>> sums;
    vector<vector<int>> nums;
    int n;
    int m;
public:
    NumMatrix(vector<vector<int>> matrix) {
        int n = matrix.size();
        if(n == 0) {
            return;
        }
        int m = matrix[0].size();
        if(m == 0) {
            return;
        }
        vector<vector<int>> sums(n, vector<int>(m, 0));
        sums[0][0] = matrix[0][0];
        for(int j = 1; j < m; j++) {
            sums[0][j] = sums[0][j-1] + matrix[0][j];
        }
        for(int i = 1; i < n; i++) {
            sums[i][0] = sums[i-1][0] + matrix[i][0];
        }
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {
                sums[i][j] = sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] + matrix[i][j];
            }
        }
        this->n = n;
        this->m = m;
        this->nums = matrix;
        this->sums = sums;
    }
    
    void update(int row, int col, int val) {
        int diff = val - nums[row][col];
        nums[row][col] = val;
        for(int i = row; i < n; i++) {
            for(int j = col; j < m; j++) {
                sums[i][j] += diff;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if(row1 == 0 && col1 == 0) {
            return sums[row2][col2];
        } else if(row1 == 0) {
            return sums[row2][col2] - sums[row2][col1-1];
        } else if(col1 == 0) {
            return sums[row2][col2] - sums[row1-1][col2];
        } else {
            return sums[row2][col2] - sums[row1-1][col2]
                   - sums[row2][col1-1] + sums[row1-1][col1-1];
        }
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
