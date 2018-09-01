class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        int ans = 10;
        int unique_digits = 9;
        int available_digits = 9;
        while (n-- > 1 && available_digits > 0) {
            unique_digits *= available_digits;
            ans += unique_digits;
            available_digits--;
        }
        return ans;
    }
};
