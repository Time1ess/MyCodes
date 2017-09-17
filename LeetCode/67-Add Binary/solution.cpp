// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-17 09:30
// Last modified: 2017-09-17 09:30
// Filename: solution.cpp
// Description:
class Solution {
public:
    string addBinary(string a, string b) {
        int len_a = a.length();
        int len_b = b.length();
        string s(max(len_a, len_b), '0');
        int la = len_a, lb = len_b;
        int ls = s.length();
        int k = 0, add = 0;
        while(la && lb)
        {
            --la, --lb;
            k = a[la] + b[lb] - 2 * '0' + add;
            add = k / 2;
            k %= 2;
            s[--ls] = k + '0';
        }
        while(la)
        {
            --la;
            k = a[la] + add - '0';
            add = k / 2;
            k %= 2;
            s[--ls] = k + '0';
        }
        while(lb)
        {
            --lb;
            k = b[lb] + add - '0';
            add = k / 2;
            k %= 2;
            s[--ls] = k + '0';
        }
        if(add)
            return "1"+s;
        else
            return s;
    }
};
