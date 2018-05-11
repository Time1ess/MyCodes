class Solution {
public:
    /*
     * @param n: A long integer
     * @return: An integer, denote the number of trailing zeros in n!
     */
    long long trailingZeros(long long n) {
        // write your code here, try to do it without arithmetic operators.
        long long cnt = 0;
        for(long long b = 5; b <= n; b *= 5)
            cnt += n / b;
        return cnt;
    }
};
