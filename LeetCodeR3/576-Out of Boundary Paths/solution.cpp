class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        if (N == 0) {
            return 0;
        }
        vector<vector<unsigned int>> cnts(m, vector<unsigned int>(n, 0));
        for (int k = 1; k <= N; k++) {
            vector<vector<unsigned int>> tmp_cnts(cnts);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    tmp_cnts[i][j] = ((i == 0 ? 1 : cnts[i-1][j]) +
                        (i == m - 1 ? 1 : cnts[i+1][j]) +
                        (j == 0 ? 1 : cnts[i][j-1]) +
                        (j == n - 1 ? 1 : cnts[i][j+1])) % 1000000007;
                }
            }
            cnts = tmp_cnts;
        }
        return cnts[i][j];
    }
};
