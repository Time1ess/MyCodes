class Solution {
public:
    /*
     * @param A: An integer array
     * @param B: An integer array
     * @return: a double whose format is *.5 or *.0
     */
    int get_kth(vector<int> &a, vector<int> &b, int l1, int r1, int l2, int r2, int k)
    {
        if(l1 >= r1) // a runs out, select from b
            return b[l2 + k - 1];
        if(l2 >= r2) // same for b
            return a[l1 + k - 1];
        if(k == 1)  // kth min, first elem in a or b
            return min(a[l1], b[l2]);
        int k1 = min(r1, l1 + k / 2);
        int k2 = min(r2, l2 + k / 2);
        if(a[k1 - 1] < b[k2 - 1])
            return get_kth(a, b, k1, r1, l2, r2, k - (k1 - l1));
        else
            return get_kth(a, b, l1, r1, k2, r2, k - (k2 - l2));
    }
    double findMedianSortedArrays(vector<int> &A, vector<int> &B) {
        // write your code here
        int m = A.size(), n = B.size();
        int l = (m + n + 1) >> 1;
        int r = (m + n + 2) >> 1;
        return (get_kth(A, B, 0, m, 0, n, l) + get_kth(A, B, 0, m, 0, n, r)) / 2.0;
    }
};
