class Solution {
public:
    double search(vector<int>& A, vector<vector<double>>& mem, int n, int k) {
        if (mem[n][k] > 0) {
            return mem[n][k];
        }
        if (n < k) {
            return 0;
        }
        double cur = 0;
        for (int i = n - 1; i >= 0; i--) {
            cur += A[i];
            mem[n][k] = max(mem[n][k], search(A, mem, i, k-1) + cur / (n-i));
        }
        return mem[n][k];
    }
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>> mem(n+1, vector<double>(K+1, 0));
        double cur = 0;
        for (int i = 0; i < n; i++) {
            cur += A[i];
            mem[i+1][1] = cur / (i+1);
        }
        return search(A, mem, n, K);
    }
};
