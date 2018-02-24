class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0)
            return false;
        int n = matrix[0].size();
        if(n == 0)
            return false;
        int l = 0, r = m * n;
        while(l < r)
        {
            int k = l + (r - l) / 2;
            int row = k / n;
            int col = k % n;
            if(matrix[row][col] == target)
                return true;
            else if(matrix[row][col] < target)
                l = k + 1;
            else
                r = k;
        }
        return false;
    }
};
