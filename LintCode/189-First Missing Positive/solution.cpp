class Solution {
public:
    /**
     * @param A: An array of integers
     * @return: An integer
     */
    int firstMissingPositive(vector<int> &A) {
        // write your code here
        int n = A.size();
        int i = 0;
        while(i < n)
        {
            if(A[i] > 0 && A[i] != i+1 && A[i] <= n && A[A[i] - 1] != A[i])
                swap(A[A[i] - 1], A[i]);
            else
                i++;
        }
        for(int i = 0; i < n; i++)
            if(A[i] != i + 1)
                return i + 1;
        return n + 1;
    }
};
