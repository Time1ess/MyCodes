class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int n = A.size(), ans = 0, l = -1, r = -1;
        for(int i = 0; i < n; i++)
        {
            if(A[i] > R)
                r = i;
            if(A[i] >= L)
                l = i;
            ans += l - r;
        }
        return ans;
    }
};
