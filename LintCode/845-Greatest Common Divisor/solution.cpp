class Solution {
public:
    /**
     * @param a: the given number
     * @param b: another number
     * @return: the greatest common divisor of two numbers
     */
    int gcd(int a, int b) {
        // write your code here
        return b == 0 ? a : gcd(b, a%b);
    }
};
