// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-11 15:13
// Last modified: 2017-03-11 15:13
// Filename: solution.cpp
// Description:
class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string s="";
        int cnt = 0;
        for(int i=S.length()-1; i >= 0; i--)
        {
            if(S[i] != '-')
            {
                if(cnt == K)
                {
                    s += '-';
                    cnt = 0;
                }
                s += toupper(S[i]);
                cnt++;
            }
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
