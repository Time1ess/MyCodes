class Solution {
public:
    /**
     * @param A: an integer sorted array
     * @param target: an integer to be inserted
     * @return: a list of length 2, [index1, index2]
     */
    int find_first(vector<int> &A, int target)
    {
        int n = A.size();
        int l = 0, r = n;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(A[m] < target)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
    vector<int> searchRange(vector<int> &A, int target) {
        // write your code here
        int n = A.size();
        int left = find_first(A, target);
        int right = find_first(A, target + 1) - 1;
        if(left == n || A[left] != target)
            return {-1, -1};
        return {left, right};
    }
};
