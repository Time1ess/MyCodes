class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int n = A.size();
        int ans = 0;
        int j = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] >= L && A[i] <= R) {
                ans += i - j + 1;
                cnt = i - j + 1;
            } else if (A[i] < L) {
                ans += cnt;
            } else {
                j = i + 1;
                cnt = 0;
            }
        }
        return ans;
    }
};
