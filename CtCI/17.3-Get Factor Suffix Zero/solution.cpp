class Factor {
public:
    int getFactorSuffixZero(int n) {
        // write code here
        int ans = 0;
        // Count numbers of 5
        for(long long base = 5; base <= n; base *= 5) {
            ans += n / base;
        }
        return ans;
    }
};
