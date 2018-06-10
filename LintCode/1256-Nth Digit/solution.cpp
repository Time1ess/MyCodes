class Solution {
public:
    int findNthDigit(int n) {
        long long digits = 1;
        long long num_cnt = 9;
        while (digits * num_cnt < n) {
            n -= digits * num_cnt;
            digits++;
            num_cnt *= 10;
        }
        long long s = pow(10, digits-1);
        long long e = pow(10, digits);
        while (n > digits) {
            long long m = s + (e - s) / 2;
            long long num_digits = digits * (m - s);
            if (n <= num_digits) {
                e = m;
            } else {
                s = m;
                n -= num_digits;
            }
        }
        for (int i = 0; i < digits - n; i++)
            s /= 10;
        return s % 10;
    }
};
