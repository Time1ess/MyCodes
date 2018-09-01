class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>> dp(n+1, vector<double>(K+1, 0));
        double cur = 0;
        for (int i = 0; i < n; i++) {
            cur += A[i];
            dp[i+1][1] = cur / (i+1);
        }
        for (int k = 2; k <= K; k++) {
            for (int i = k; i <= n; i++) {
                cur = 0;
                for (int j = i - 1; j >= 0; j--) {
                    cur += A[j];
                    dp[i][k] = max(dp[i][k], dp[j][k-1] + cur / (i-j));
                }
            }
        }
        return dp[n][K];
    }
};
