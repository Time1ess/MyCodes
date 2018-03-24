class Solution {
public:
    /**
     * @param n: a number
     * @param d: digit needed to be rorated
     * @return: a number
     */
    int leftRotate(int n, int d) {
        // write code here
        if(n < 0)
            return -1;
        d %= 32;
        return n << d | n >> (32 - d);
    }
};
