class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        int ans = 0;
        unordered_set<int> nums(A.begin(), A.end());
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = A[i], b = A[j];
                int len = 2;
                while (nums.find(a+b) != nums.end()) {
                    b = a + b;
                    a = b - a;
                    len++;
                }
                ans = max(ans, len);
            }
        }
        return ans > 2 ? ans : 0;
    }
};
