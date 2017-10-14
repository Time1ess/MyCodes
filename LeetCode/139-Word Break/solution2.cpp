// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-14 16:52
// Last modified: 2017-10-14 16:52
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int size = s.length();
        if(size == 0)
            return false;
        set<string> showups(wordDict.begin(), wordDict.end());
        bool dp[size+1] = {true};
        for(int i = 1; i <= size; i++)
            for(int j = 0; j <= i; j++)
                if(dp[j] && showups.find(s.substr(j, i - j)) != showups.end())
                {
                    dp[i] = true;
                    break;
                }
        return dp[size];
    }
};
