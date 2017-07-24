// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-24 13:45
// Last modified: 2017-07-24 13:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    int countSubstrings(string s) {
        int size = s.length();
        int cnt = 0;
        int l, r;
        for(int i = 0; i < size; i++)
        {
            l = r = i;
            while(l >= 0 && r < size)
                if(s[l] == s[r])
                {
                    l--, r++;
                    cnt++;
                }
                else
                    break;
            l = i - 1;
            r = i;
            while(l >= 0 && r < size)
                if(s[l] == s[r])
                {
                    l--, r++;
                    cnt++;
                }
                else
                    break;
        }
        return cnt;
    }
};
