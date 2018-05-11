class Solution {
public:
    /**
     * @param a: A 32bit integer
     * @param b: A 32bit integer
     * @param n: A 32bit integer
     * @return: An integer
     */
    int fastPower(int a, int b, int n) {
        // write your code here
        if(n == 0)
            return 1 % b;
        else if(n == 1)
            return a % b;
        long long t = fastPower(a, b, n / 2);
        if((n & 0x1) == 0)
            return (t * t) % b;
        else
            return (((t * t) % b) * a) % b;
    }
};
