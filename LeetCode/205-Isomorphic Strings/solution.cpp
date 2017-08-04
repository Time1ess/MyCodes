// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-04 10:33
// Last modified: 2017-08-04 10:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int mappings[2][128] = {{0}}, cnt = 0;
        for(int i = 0; i < s.length(); i++)
            if(mappings[0][s[i]] == 0 && mappings[1][t[i]] == 0)
                mappings[0][s[i]] = mappings[1][t[i]] = ++cnt;
            else if(mappings[0][s[i]] != mappings[1][t[i]])
                return false;
        return true;
    }
};
