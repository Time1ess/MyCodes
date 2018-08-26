class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        int n = matrix[0].size();
        if (n == 0) {
            return {};
        }
        int l = 0, r = n - 1, t = 0, b = m - 1;
        vector<int> ans;
        while (l <= r && t <= b) {
            // Top
            for (int j = l; j <= r; j++) {
                ans.push_back(matrix[t][j]);
            }
            // Right
            if (b - t > 0) {
                for (int i = t + 1; i <= b; i++) {
                    ans.push_back(matrix[i][r]);
                }
            }
            // Bottom
            if (b - t > 0 && r - l > 0) {
                for (int j = r - 1; j >= l; j--) {
                    ans.push_back(matrix[b][j]);
                }
            }
            // Left
            if (b - t > 1 && r - l > 0) {
                for (int i = b - 1; i >= t + 1; i--) {
                    ans.push_back(matrix[i][l]);
                }
            }
            l++, r--, t++, b--;
        }
        return ans;
    }
};
