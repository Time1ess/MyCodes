class Solution {
public:
    /*
     * @param x: An integer
     * @param y: An integer
     * @return: nothing
     */
    void swap(int& x, int& y) {
        // write your code here
        x ^= y;
        y ^= x;
        x ^= y;
    }
};
