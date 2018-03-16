class Solution {
public:
    /**
     * @param a: An integer
     * @param b: An integer
     * @return: The sum of a and b
     */
    int aplusb(int a, int b) {
        // write your code here
        while(b != 0)
        {
            int t = a ^ b;
            b = (a & b) << 1;
            a = t;
        }
        return a;
    }
};
