class Solution {
public:
    double Power(double base, int exponent) {
        int abs_exponent = abs(exponent);
        if(abs(base) < 1e-6)
            return 0;
        double ret;
        if(abs_exponent == 0)
            ret = 1;
        else if(abs_exponent == 1)
            ret = base;
        else
            ret = Power(base * base, abs_exponent >> 1) * (abs_exponent & 0x1 == 0 ? 1 : base);
        return exponent > 0 ? ret : 1 / ret;
    }
};
