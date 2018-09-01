class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (auto str : strs) {
            int num_zeros = 0;
            int num_ones = 0;
            for (auto ch : str) {
                if (ch == '0') {
                    num_zeros++;
                } else {
                    num_ones++;
                }
            }
            for (int x = m; x >= num_zeros; x--) {
                for (int y = n; y >= num_ones; y--) {
                    dp[x][y] = max(dp[x][y], dp[x-num_zeros][y-num_ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
