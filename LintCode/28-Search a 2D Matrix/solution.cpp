class Solution {
public:
    /*
     * @param matrix: matrix, a list of lists of integers
     * @param target: An integer
     * @return: a boolean, indicate whether matrix contains target
     */
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        // write your code here
        int m = matrix.size();
        if(m == 0)
            return false;
        int n = matrix[0].size();
        if(n == 0)
            return false;
        int l = 0, r = m * n - 1;
        while(l <= r)
        {
            int k = l + (r - l) / 2;
            int row = k / n;
            int col = k % n;
            if(matrix[row][col] == target)
                return true;
            else if(matrix[row][col] < target)
                l = k + 1;
            else
                r = k - 1;
        }
        return false;
    }
};
