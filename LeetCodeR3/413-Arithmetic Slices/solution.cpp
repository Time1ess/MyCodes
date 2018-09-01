class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        int cur = 0;
        int ans = 0;
        for (int i = 2; i < n; i++) {
            if (A[i] - A[i-1] == A[i-1] - A[i-2]) {
                cur++;
                ans += cur;
            } else {
                cur = 0;
            }
        }
        return ans;
    }
};
