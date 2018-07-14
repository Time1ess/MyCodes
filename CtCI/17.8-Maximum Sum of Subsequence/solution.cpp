class MaxSum {
public:
    int getMaxSum(vector<int> A, int n) {
        // write code here
        int ans = INT_MIN;
        int cur = INT_MIN;
        for(int i = 0; i < n; i++) {
            if(cur < 0) {
                cur = A[i];
            } else {
                cur += A[i];
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};
