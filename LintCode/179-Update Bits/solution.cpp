class Solution {
public:
    /**
     * @param n: An integer
     * @param m: An integer
     * @param i: A bit position
     * @param j: A bit position
     * @return: An integer
     */
    int updateBits(int n, int m, int i, int j) {
        // write your code here
        int mask = 0;
        if(j < 31)
            mask = ~((1 << (j+1)) - (1 << i));
        else
            mask = (1 << i) - 1;
        return (mask & n) + (m << i);
    }
};
