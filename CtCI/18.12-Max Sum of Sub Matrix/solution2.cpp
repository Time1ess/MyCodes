class SubMatrix {
public:
    void precompute_sums(vector<vector<int>>& mat, vector<vector<int>>& sums, int n) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == 0 && j == 0) {
                    sums[i][j] = mat[i][j];
                } else if(i == 0) {
                    sums[i][j] = sums[i][j-1] + mat[i][j];
                } else if(j == 0) {
                    sums[i][j] = sums[i-1][j] + mat[i][j];
                } else {
                    sums[i][j] = sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] + mat[i][j];
                }
            }
        }
    }
    int submatrix_colsum(vector<vector<int>>& sums, int r0, int r1, int col) {
        if(r0 == 0 && col == 0) {
            return sums[r1][col];
        } else if(r0 == 0) {
            return sums[r1][col] - sums[r1][col-1];
        } else if(col == 0) {
            return sums[r1][col] - sums[r0-1][col];
        } else {
            return sums[r1][col] - sums[r1][col-1] - sums[r0-1][col] + sums[r0-1][col-1];
        }
    }
    int submatrix_maxsum(vector<vector<int>>& sums, int r0, int r1, int n) {
        int cur = submatrix_colsum(sums, r0, r1, 0);
        int ans = cur;
        for(int i = 1; i < n; i++) {
            int colsum = submatrix_colsum(sums, r0, r1, i);
            cur = cur < 0 ? colsum : cur + colsum;
            ans = max(ans, cur);
        }
        return ans;
    }
    int sumOfSubMatrix(vector<vector<int> > mat, int n) {
        // write code here
        vector<vector<int>> sums(n, vector<int>(n, 0));
        precompute_sums(mat, sums, n);
        int ans = 0;
        for(int r0 = 0; r0 < n; r0++) {
            for(int r1 = r0; r1 < n; r1++) {
                ans = max(ans, submatrix_maxsum(sums, r0, r1, n));
            }
        }
        return ans;
    }
};
