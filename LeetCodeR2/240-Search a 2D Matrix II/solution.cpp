class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0)
            return false;
        int n = matrix[0].size();
        if(n == 0)
            return false;
        int r = 0;
        int c = n - 1;
        while(r < m && c >= 0)
        {
            if(matrix[r][c] == target)
                return true;
            else if(matrix[r][c] < target)
                r++;
            else
                c--;
        }
        return false;
    }
};
