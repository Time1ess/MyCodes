class Solution {
public:
    /*
     * @param A: sorted integer array A which has m elements, but size of A is m+n
     * @param m: An integer
     * @param B: sorted integer array B which has n elements
     * @param n: An integer
     * @return: nothing
     */
    void mergeSortedArray(int A[], int m, int B[], int n) {
        // write your code here
        int i = m - 1, j = n - 1, k = m + n - 1;
        while(i >= 0 && j >= 0)
        {
            if(A[i] > B[j])
                A[k--] = A[i--];
            else
                A[k--] = B[j--];
        }
        while(i >= 0)
            A[k--] = A[i--];
        while(j >= 0)
            A[k--] = B[j--];
    }
};
