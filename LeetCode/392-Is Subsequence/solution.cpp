// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-25 13:40
// Last modified: 2016-10-25 13:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = s.length()-1;
        int j = t.length()-1;
        while(i>=0&&j>=0)
        {
            if(s[i]==t[j])
                i--;
            j--;
        }
        if(i==-1)
            return true;
        return false;
    }
};
