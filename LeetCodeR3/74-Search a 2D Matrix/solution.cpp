class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int t = 0, b = matrix.size();
        if (b == 0) {
            return false;
        }
        int n = matrix[0].size();
        if (n == 0) {
            return false;
        }
        while (t < b) {
            int m = t + (b - t) / 2;
            if (matrix[m][0] == target) {
                return true;
            } else if (matrix[m][0] > target) {
                b = m;
            } else if (matrix[m][n-1] < target){
                t = m + 1;
            } else {
                int l = 0, r = n;
                while (l < r) {
                    int cm = l + (r - l) / 2;
                    if (matrix[m][cm] == target) {
                        return true;
                    } else if (matrix[m][cm] > target) {
                        r = cm;
                    } else {
                        l = cm + 1;
                    }
                }
                return false;
            }
        }
        return false;
    }
};
