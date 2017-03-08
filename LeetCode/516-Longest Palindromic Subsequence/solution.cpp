// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-08 20:59
// Last modified: 2017-03-08 20:59
// Filename: solution.cpp
// Description:
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.length();
        if(size == 0)
            return 0;
        int dp[size][size] = {0};
        int left, right, add;
        for(int len=1; len <= size; len++)
        {
            for(left=0; left + len <= size; left++)
            {
                right = left + len - 1;
                if(left == right)
                    dp[left][left] = 1;
                else if(left + 1 == right)
                    dp[left][right] = s[left] == s[right] ? 2 : 1;
                else
                {
                    add = s[left] == s[right] ? 2 : 0;
                    dp[left][right] = max(dp[left+1][right], dp[left][right-1]);
                    dp[left][right] = max(dp[left][right], dp[left+1][right-1] + add);
                }
            }
        }
        return dp[0][size-1];
    }
};
