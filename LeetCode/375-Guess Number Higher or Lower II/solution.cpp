// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-26 09:43
// Last modified: 2017-05-26 09:43
// Filename: solution.cpp
// Description:
class Solution {
public:
    int dp(vector<vector<int>> &t, int s, int e)
    {
        if(s >= e)
            return 0;
        if(t[s][e] != 0)
            return t[s][e];
        int res = INT_MAX;
        for(int i = s; i <= e; i++)
        {
            int tmp = i + max(dp(t, s, i-1), dp(t, i+1, e));
            res = min(res, tmp);
        }
        t[s][e] = res;
        return res;
    }
    int getMoneyAmount(int n) {
        vector<vector<int>> t(n+1, vector<int>(n+1, 0));
        return dp(t, 1, n);
    }
};
