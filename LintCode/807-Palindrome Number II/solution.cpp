class Solution {
public:
    /**
     * @param n: non-negative integer n.
     * @return: return whether a binary representation of a non-negative integer n is a palindrome.
     */
    bool isPalindrome(int n) {
        // Write your code here
        int m = 0;
        int t = n;
        while(t)
        {
            m = m << 1 | (t & 0x1);
            t >>= 1;
        }
        return m == n;
    }
};
