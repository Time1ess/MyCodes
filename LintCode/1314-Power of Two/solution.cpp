class Solution {
public:
    /**
     * @param n: an integer
     * @return: if n is a power of two
     */
    bool isPowerOfTwo(int n) {
        // Write your code here
        return n > 0 && (n & (n-1)) == 0;
    }
};
