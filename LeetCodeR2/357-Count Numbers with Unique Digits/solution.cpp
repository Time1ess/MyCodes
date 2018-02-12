class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0)
            return 1;
        int ans = 10;
        if(n == 1)
            return ans;
        else
        {
            for(int d = 2; d <= min(10, n); d++)
            {
                int x = 9;
                for(int t = 0; t < d - 1; t++)
                    x *= (9 - t);
                ans += x;
            }
        }
        return ans;
    }
};
