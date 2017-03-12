// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 16:26
// Last modified: 2017-03-12 16:26
// Filename: solution2.cpp
// Description:
class Solution {
public:
    string decodeString(string &s, int &i)
    {
        string ans = "", sub;
        while(i < s.length() && s[i] != ']')
        {
            if(!(s[i] >= '0' && s[i] <= '9'))
                ans += s[i++];
            else
            {
                int cnt = 0;
                while(i < s.length() && s[i] >= '0' && s[i] <= '9')
                {
                    cnt = cnt * 10 + s[i] -'0';
                    i++;
                }
                i++;  // skip [
                sub = decodeString(s, i);
                i++;  // skip ]
                while(cnt-- > 0)
                    ans += sub;
            }
        }
        return ans;
    }
    string decodeString(string s) {
        int i = 0;
        return decodeString(s, i);
    }
};
