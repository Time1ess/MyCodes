class Solution {
public:
    void merge_sort(vector<int>& A, vector<int>& tmp, long long& ans, int s, int e) {
        if(s + 1 >= e) {
            return;
        }
        int m = s + (e - s) / 2;
        merge_sort(A, tmp, ans, s, m);
        merge_sort(A, tmp, ans, m, e);
        merge(A, tmp, ans, s, m, e);
    }
    
    void merge(vector<int>& A, vector<int>& tmp, long long& ans, int s, int m, int e) {
        int i = m - 1, j = e - 1;  // Start of two segments
        int k = e - 1;
        while(i >= s && j >= m) {
            if(A[i] > A[j]) {  // Reverse pairs found
                ans += j - m + 1;
                tmp[k--] = A[i--];
            } else {
                tmp[k--] = A[j--];
            }
        }
        while(i >= s) {
            tmp[k--] = A[i--];
        }
        while(j >= m) {
            tmp[k--] = A[j--];
        }
        for(int l = s; l < e; l++) {
            A[l] = tmp[l];
        }
    }
    /**
     * @param A: an array
     * @return: total of reverse pairs
     */
    long long reversePairs(vector<int> &A) {
        // write your code here
        long long ans = 0;
        vector<int> tmp(A.size(), 0);
        merge_sort(A, tmp, ans, 0, A.size());
        return ans;
    }
};
