class Max {
public:
    int flip(int x) {
        return 1 ^ x;
    }
    // If x is positive, return 1
    // If x is negative, return 0
    int sign(int x) {
        return flip((x >> 31 & 0x1));
    }
    int getMax(int a, int b) {
        int c = a - b;  // May overflow
        
        int sign_a = sign(a);
        int sign_b = sign(b);
        int sign_c = sign(c);

        // If a > 0 && b < 0, k = 1
        // If a < 0 && b > 0, k = 0
        int use_sign_a = sign_a ^ sign_b;
        int use_sign_c = flip(use_sign_a);
        int k = use_sign_a * sign_a + use_sign_c * sign_c;
        int q = flip(k);
        
        return k * a + q * b;
    }
};
