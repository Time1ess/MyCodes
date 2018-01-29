class Solution {
public:
    /*
     * @param matrix: A list of lists of integers
     * @param target: An integer you want to search in matrix
     * @return: An integer indicate the total occurrence of target in the given matrix
     */
    int searchMatrix(vector<vector<int>> &matrix, int target) {
        // write your code here
        int m = matrix.size();
        if(m == 0)
            return 0;
        int n = matrix[0].size();
        if(n == 0)
            return 0;
        int r = 0, c = n - 1;
        int cnt = 0;
        while(r < m && c >= 0)
        {
            if(matrix[r][c] == target)
            {
                cnt++;
                r++, c--;
            }
            else if(matrix[r][c] > target)
                c--;
            else
                r++;
        }
        return cnt;
    }
};
