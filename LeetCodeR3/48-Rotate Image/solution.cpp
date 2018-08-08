class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int s = 0, e = n - 1;
        while(s < e) {
            int len = e - s;
            for(int offset = 0; offset < len; offset++) {
                int t = matrix[s][s+offset];
                matrix[s][s+offset] = matrix[e-offset][s];
                matrix[e-offset][s] = matrix[e][e-offset];
                matrix[e][e-offset] = matrix[s+offset][e];
                matrix[s+offset][e] = t;
            }
            s++, e--;
        }
    }
};
