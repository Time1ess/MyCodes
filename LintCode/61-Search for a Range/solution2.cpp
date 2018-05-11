class Solution {
public:
    /**
     * @param A: an integer sorted array
     * @param target: an integer to be inserted
     * @return: a list of length 2, [index1, index2]
     */
    vector<int> searchRange(vector<int> &A, int target) {
        // write your code here
        int n = A.size();
        int left = lower_bound(A.begin(), A.end(), target) - A.begin();
        int right = upper_bound(A.begin(), A.end(), target) - A.begin() - 1;
        if(left == n || A[left] != target)
            return {-1, -1};
        return {left, right};
    }
};
