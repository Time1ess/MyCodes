class Solution {
public:
    /**
     * @param A: A list of integers
     * @return: A boolean
     */
    bool canJump(vector<int> &A) {
        // write your code here
        int n = A.size();
        vector<bool> can_reach(n, false);
        can_reach[n-1] = true;
        for(int i = n - 2; i >= 0; i--)
            for(int j = i + 1; j < n && j <= i + A[i]; j++)
                can_reach[i] = can_reach[i] || can_reach[j];
        return can_reach[0];
    }
};
