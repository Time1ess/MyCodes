class Solution {
public:
    /*
     * @param A: An integers array.
     * @return: return any of peek positions.
     */
    int findPeak(vector<int>& A) {
        // write your code here
        int l = 1, r = A.size() - 2;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(A[m] > A[m-1] && A[m] > A[m+1])
                return m;
            else if(A[m] > A[m-1])
                l = m + 1;
            else
                r = m - 1;
        }
        return l;
    }
};
