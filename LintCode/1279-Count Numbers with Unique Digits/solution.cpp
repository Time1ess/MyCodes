class Solution {
public:
    /**
     * @param n: a non-negative integer
     * @return: number of numbers with unique digits
     */
    int arrangements(int x) {
        int t = 1;
        x--;
        for(int i = 1; i <= x; i++)
            t *= (10 - i);
        return 9 * t;
    }
    int countNumbersWithUniqueDigits(int n) {
        // Write your code here 
        if(n == 1)
            return 10;
        int ans = 10;
        for(int i = 2; i <= min(n, 10); i++)
            ans += arrangements(i);
        return ans;
    }
};
