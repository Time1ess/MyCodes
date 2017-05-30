// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-27 14:10
// Last modified: 2017-05-27 14:10
// Filename: solution3.cpp
// Description:
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int rlen = ring.length(), klen = key.length();
        int dp[klen + 1][rlen] = {0}, dis;
        unordered_map<char, vector<int>> mm;
        for(int i = 0; i < rlen; i++)
            mm[ring[i]].push_back(i);
        for(int k = klen-1; k >= 0; k--)
            for(int r = 0; r < rlen; r++)
            {
                dp[k][r] = INT_MAX;
                for(auto rr: mm[key[k]])
                    dp[k][r] = min(dp[k][r], min(abs(rr-r), rlen - abs(rr - r)) + dp[k+1][rr]);
            }
        return dp[0][0] + klen;
    }
};
