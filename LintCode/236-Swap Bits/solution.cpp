class Solution {
public:
    /*
     * @param x: An integer
     * @return: An integer
     */
    int swapOddEvenBits(int x) {
        // write your code here
        const unsigned int odd_mask = 0x55555555;
        const unsigned int even_mask = 0xAAAAAAAA;
        unsigned int y = x;
        return ((y & odd_mask) << 1) | ((y & even_mask) >> 1);
    }
};
