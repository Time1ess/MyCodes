class Solution {
public:
    /**
     * @param a: a integer represent the length of one edge
     * @param b: a integer represent the length of one edge
     * @param c: a integer represent the length of one edge
     * @return: whether three edges can form a triangle
     */
    bool isValidTriangle(int a, int b, int c) {
        // write your code here
        return a > 0 && b > 0 && c > 0 && a + b > c && a - b < c;
    }
};
