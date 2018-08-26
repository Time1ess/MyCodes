class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int n = A.size();
        unordered_map<int, int> sum_cnts;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum_cnts[A[i]+B[j]]++;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans += sum_cnts[-(C[i]+D[j])];
            }
        }
        return ans;
    }
};
