class Solution {
public:
    /**
     * @param matrix: the given matrix
     * @return: True if and only if the matrix is Toeplitz
     */
    bool isToeplitzMatrix(vector<vector<int>> &matrix) {
        // Write your code here
        int m = matrix.size();
        if (m == 0) {
            return true;
        }
        int n = matrix[0].size();
        if (n == 0) {
            return true;
        }
        for (int y_ = n - 1; y_ >= 0; y_--) {
            int x = 1, y = y_ + 1;
            while (x < m && y < n) {
                if (matrix[x][y] != matrix[x-1][y-1]) {
                    return false;
                }
                x++, y++;
            }
        }
        for (int x_ = 1; x_ < m; x_++) {
            int x = x_ + 1, y = 1;
            while (x < m && y < n) {
                if (matrix[x][y] != matrix[x-1][y-1]) {
                    return false;
                }
                x++, y++;
            }
        }
        return true;
    }
};
