// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-27 13:48
// Last modified: 2017-05-27 13:48
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int rlen = ring.length(), klen = key.length();
        // dp[k][r]: The minimum cost to finish the key from the k-th pos
        //           and the current 12:00 char is ring[r]
        int dp[klen + 1][rlen] = {0}, dis;
        for(int k = klen-1; k >= 0; k--)
            for(int r = 0; r < rlen; r++)
            {
                dp[k][r] = INT_MAX;
                for(int rr = 0; rr < rlen; rr++)
                    if(ring[rr] == key[k])
                        dp[k][r] = min(dp[k][r], min(abs(rr-r), rlen - abs(rr - r)) + dp[k+1][rr]);
            }
        return dp[0][0] + klen;
    }
};
