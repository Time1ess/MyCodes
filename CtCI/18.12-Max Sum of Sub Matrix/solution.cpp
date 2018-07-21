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
    int submatrix_sum(vector<vector<int>>& sums, int r0, int r1, int c0, int c1) {
        if(r0 == 0 && c0 == 0) {
            return sums[r1][c1];
        } else if(r0 == 0) {
            return sums[r1][c1] - sums[r1][c0-1];
        } else if(c0 == 0) {
            return sums[r1][c1] - sums[r0-1][c1];
        } else {
            return sums[r1][c1] - sums[r0-1][c1] - sums[r1][c0-1] + sums[r0-1][c0-1];
        }
    }
    int sumOfSubMatrix(vector<vector<int> > mat, int n) {
        // write code here
        vector<vector<int>> sums(n, vector<int>(n, 0));
        precompute_sums(mat, sums, n);
        int ans = 0;
        for(int r0 = 0; r0 < n; r0++) {
            for(int r1 = r0; r1 < n; r1++) {
                for(int c0 = 0; c0 < n; c0++) {
                    for(int c1 = c0; c1 < n; c1++) {
                        ans = max(ans, submatrix_sum(sums, r0, r1, c0, c1));
                    }
                }
            }
        }
        return ans;
    }
};
