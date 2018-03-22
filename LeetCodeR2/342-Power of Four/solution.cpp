#define mask 0x55555555

class Solution {
public:
    bool isPowerOfFour(int num) {
        int t = num & mask;
        return t && (num | mask) == mask && (t & (t-1)) == 0;
    }
};
