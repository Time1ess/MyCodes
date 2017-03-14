// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-14 17:07
// Last modified: 2017-03-14 17:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string ans = "";
        int ssize = s.length(), dsize = d.size();
        int si, sd, al, dl;
        for(int i = 0; i < dsize; i++)
        {
            si = sd = 0;
            dl = d[i].length();
            while(si < ssize && sd < dl)
                sd += s[si++] == d[i][sd];
            al = ans.length();
            if((sd == dl) && (dl > al || (dl == al && d[i] < ans)))
                ans = d[i];
        }
        return ans;
    }
};
