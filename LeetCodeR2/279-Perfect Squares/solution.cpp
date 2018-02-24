class Solution {
public:
    int numSquares(int n) {
        static vector<int> dp({0});
        int i = dp.size();
        while(i <= n)
        {
            int sqrt_i = sqrt(i);
            dp.push_back(INT_MAX);
            if(sqrt_i * sqrt_i == i)
                dp[i] = 1;
            else
                for(int j = 1; j * j <= i; j++)
                    dp[i] = min(dp[i], dp[i - j * j] + 1);
            i++;
        }
        return dp[n];
    }
};
