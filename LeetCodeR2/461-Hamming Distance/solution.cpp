class Solution {
public:
    int hammingDistance(int x, int y) {
        int t = x ^ y;
        int n = 0;
        while(t)
        {
            n++;
            t &= (t - 1);
        }
        return n;
    }
};
