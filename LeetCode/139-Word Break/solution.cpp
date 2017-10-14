// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-14 16:45
// Last modified: 2017-10-14 16:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int size = s.length();
        if(size == 0)
            return false;
        set<string> showups(wordDict.begin(), wordDict.end());
        bool dp[size][size];
        memset(dp, 0, sizeof(dp));
        for(int len = 1; len <= size; len++)
        {
            for(int l = 0; l + len <= size; l++)
            {
                int r = l + len - 1;
                if(showups.find(s.substr(l, len)) != showups.end())
                {
                    dp[l][r] = true;
                    continue;
                }
                for(int k = l; k < r; k++)
                    if(dp[l][k] && dp[k+1][r])
                    {
                        dp[l][r] = true;
                        break;
                    }
            }
        }
        return dp[0][size-1];
    }
};
