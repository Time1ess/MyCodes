class Solution {
public:
    /*
     * @param x: the base number
     * @param n: the power number
     * @return: the result
     */
    double myPow(double x, int n) {
        // write your code here
        if(n == 0)
            return 1;
        else if(n == 1)
            return x;
        else if(n < 0)
            return 1 / x * myPow(1 / x, - (n + 1));
        double ans = myPow(x * x, n >> 1);
        if((n & 1) == 1)
            ans *= x;
        return ans;
    }
};
