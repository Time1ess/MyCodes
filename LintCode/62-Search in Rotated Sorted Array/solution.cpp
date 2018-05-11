class Solution {
public:
    /**
     * @param A: an integer rotated sorted array
     * @param target: an integer to be searched
     * @return: an integer
     */
    int search(vector<int> &A, int target) {
        // write your code here
        int n = A.size();
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r -l) / 2;
            if(A[m] == target)
                return m;
            else if(A[l] < A[m])
                if(A[l] <= target && target < A[m])
                    r = m;
                else
                    l = m + 1;
            else
                if(A[m] < target && target <= A[r - 1])
                    l = m + 1;
                else
                    r = m;
        }
        return -1;
    }
};
