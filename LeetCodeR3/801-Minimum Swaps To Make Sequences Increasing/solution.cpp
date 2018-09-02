class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> swap(n, 0), not_swap(n, 0);
        swap[0] = 1;
        for (int i = 1; i < n; i++) {
            swap[i] = not_swap[i] = n;
            if (A[i-1] < A[i] && B[i-1] < B[i]) {
                not_swap[i] = not_swap[i-1];
                swap[i] = swap[i-1] + 1;
            }
            if (A[i-1] < B[i] && B[i-1] < A[i]) {
                not_swap[i] = min(not_swap[i], swap[i-1]);
                swap[i] = min(swap[i], not_swap[i-1] + 1);
            }
        }
        return min(swap[n-1], not_swap[n-1]);
    }
};
