// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-03 09:56
// Last modified: 2017-04-03 09:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findLUSlength(string a, string b) {
        int la = a.length(), lb = b.length();
        if(la != lb)
            return max(la, lb);
        else if(a == b)
            return -1;
        else
            return la;
    }
};
