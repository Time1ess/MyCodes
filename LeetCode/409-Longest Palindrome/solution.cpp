// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-05 21:32
// Last modified: 2016-10-05 21:32
// Filename: solution.cpp
// Description:
class Solution {
public:
    int longestPalindrome(string s) {
        map<char, int> m;
        int cnt=0;
        bool odd=false;
        for(int i=0; i<s.length(); i++)
            m[s[i]]++;
        for(int i=0; i<s.length(); i++)
        {
            if(m[s[i]]==0)
                continue;
            if(m[s[i]]%2==0)
            {
                cnt += m[s[i]];
                m[s[i]] = 0;
            }
            else if(m[s[i]]%2!=0)
            {
                cnt += m[s[i]]-1;
                m[s[i]] = 0;
                odd=true;
            }
        }
        cnt += odd?1:0;
        return cnt;
    }
};
