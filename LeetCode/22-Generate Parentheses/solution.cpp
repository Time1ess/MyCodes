// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-25 16:16
// Last modified: 2017-02-25 16:16
// Filename: solution.cpp
// Description:
class Solution {
public:
    void sub_parenthesis(vector<string> &ans, string &s, int start, int n, int pair_num, int lc, int rc)
    {
        if(start == n)
        {
            ans.push_back(s);
            return;
        }
        if(lc > 0)
            // not '(' at this pos
            sub_parenthesis(ans, s, start+1, n, pair_num, lc-1, rc);
        if(rc > pair_num)
        {
            // '(' at this pos
            s[start] = '(';
            sub_parenthesis(ans, s, start+1, n, pair_num, lc+1, rc-1);
            s[start] = ')';
        }
        
    }
    vector<string> generateParenthesis(int n) {
        string s=string(n*2, ')');
        vector<string> ans;
        if(n <= 0)
        {
            ans.push_back(s);
            return ans;
        }
        sub_parenthesis(ans, s, 0, n * 2 -1, n, 0, n * 2);
        return ans;
    }
};
