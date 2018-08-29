class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            if (abs(A[i] - i) > 1) {
                return false;
            }
        }
        return true;
    }
};
