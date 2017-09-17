// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-17 09:33
// Last modified: 2017-09-17 09:33
// Filename: solution2.cpp
// Description:
class Solution {
public:
    string addBinary(string a, string b) {
        int la = a.length() - 1, lb = b.length() - 1;
        int c = 0;
        string s;
        while(la >= 0 || lb >= 0 || c == 1)
        {
            c += la >= 0 ? a[la--] - '0': 0;
            c += lb >= 0 ? b[lb--] - '0': 0;
            s = char(c % 2 +'0') + s;
            c /= 2;
        }
        return s;
    }
};
