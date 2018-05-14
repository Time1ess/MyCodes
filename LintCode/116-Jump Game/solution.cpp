class Solution {
public:
    /**
     * @param A: A list of integers
     * @return: A boolean
     */
    bool canJump(vector<int> &A) {
        // write your code here
        int n = A.size();
        int max_length = 0;
        for(int i = 0; i < n && i <= max_length; i++)
            max_length = max(max_length, i + A[i]);
        return max_length >= n - 1;
    }
};
