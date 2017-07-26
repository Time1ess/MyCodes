// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-26 10:14
// Last modified: 2017-07-26 10:14
// Filename: solution2.cpp
// Description:
class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        char ch;
        int cnt, i;
        while(n-- > 1)
        {
            string tmp;
            i = 0;
            while(i < res.length())
            {
                ch = res[i++];
                cnt = 1;
                while(i < res.length() && res[i] == ch)
                {
                    cnt++;
                    i++;
                }
                tmp.push_back('0' + cnt);
                tmp.push_back(ch);
            }
            res = tmp;
        }
        return res;
    }
};
