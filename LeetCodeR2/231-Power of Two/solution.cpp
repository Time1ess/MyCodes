class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0)
            return false;
        int bits = 1, cnt = 0;
        while(++cnt <= 31 && bits != n)
            bits <<= 1;
        return bits == n;
    }
};
