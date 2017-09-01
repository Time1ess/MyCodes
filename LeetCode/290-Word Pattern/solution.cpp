// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-01 15:15
// Last modified: 2017-09-01 15:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        map<char, string> p2s;
        map<string, char> s2p;
        int i = 0, j = 0;
        str += " ";
        while(true)
        {
            int k = str.find(' ', j);
            if(k == -1)
                break;
            string s = str.substr(j, k - j);  // s <-> pattern[i]
            if(p2s.find(pattern[i]) == p2s.end() && s2p.find(s) == s2p.end())
                p2s[pattern[i]] = s, s2p[s] = pattern[i];
            else if(p2s[pattern[i]] != s || s2p[s] != pattern[i])
                return false;
            j = k + 1;
            i++;
        }
        if(i != pattern.size())
            return false;
        return true;
    }
};
