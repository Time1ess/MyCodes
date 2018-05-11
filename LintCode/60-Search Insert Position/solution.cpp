class Solution {
public:
    /**
     * @param A: an integer sorted array
     * @param target: an integer to be inserted
     * @return: An integer
     */
    int searchInsert(vector<int> &A, int target) {
        // write your code here
        int n = A.size();
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(A[m] == target)
                return m;
            else if(A[m] < target)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};
