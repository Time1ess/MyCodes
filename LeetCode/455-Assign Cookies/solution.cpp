// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-11-27 10:33
// Last modified: 2016-11-27 10:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0, j = 0;;
        int cnt = 0;
        int gsize = g.size();
        int ssize = s.size();
        while(i < gsize && j < ssize)
        {
            if(g[i] <= s[j])
            {
                cnt++;
                i++;
                j++;
            }
            else
                j++;
        }
        return cnt;
    }
};
