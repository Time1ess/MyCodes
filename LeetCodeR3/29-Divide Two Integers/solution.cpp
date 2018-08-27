class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
        long long ded = labs(dividend);
        long long div = labs(divisor);
        int ans = 0;
        while (ded >= div) {
            long long x = div, mul = 1;
            while ((x << 1) <= ded) {
                x <<= 1;
                mul <<= 1;
            }
            ans += mul;
            ded -= x;
        }
        return ans * sign;
    }
};
