// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-27 09:33
// Last modified: 2017-06-27 09:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    void helper(set<string> &ss, string &s, string ans, int k, int length, int lc, int rc)
    {
        if(k > length)
        {
            if(lc == rc)
            {
                if(!ss.empty())
                {
                    auto x = *ss.begin();
                    if(x.length() > ans.length())
                        return;
                    else if(x.length() < ans.length())
                        ss.clear();
                }
                ss.insert(ans);
            }
            return;
        }
        if(s[k] == '(')
            helper(ss, s, ans+s[k], k+1, length, lc+1, rc);
        else if(s[k] == ')' && lc > rc)
            helper(ss, s, ans+s[k], k+1, length, lc, rc+1);
        if(s[k] != '(' && s[k] != ')')
            helper(ss, s, ans+s[k], k+1, length, lc, rc);
        else
            helper(ss, s, ans, k+1, length, lc, rc);
    }
    vector<string> removeInvalidParentheses(string s) {
        set<string> ss;
        string ans = "";
        vector<string> vs;
        helper(ss, s, ans, 0, s.length(), 0, 0);
        for(auto x: ss)
            vs.push_back(x);
        return vs;
    }
};
