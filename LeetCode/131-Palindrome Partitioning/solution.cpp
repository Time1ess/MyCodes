// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-27 14:37
// Last modified: 2017-08-27 14:37
// Filename: solution.cpp
// Description:
class Solution {
public:
    void dfs(vector<vector<string>> &ans, vector<string> &current, string &s, int start)
    {
        if(start == s.length())
        {
            ans.push_back(current);
            return;
        }
        for(int i = start; i < s.length(); i++)
        {
            if(is_palindrome(s, start, i))
            {
                current.push_back(s.substr(start, i - start + 1));
                dfs(ans, current, s, i + 1);
                current.pop_back();
            }
        }
    }
    bool is_palindrome(string &s, int start, int end)
    {
        while(start <= end)
            if(s[start++] != s[end--])
                return false;
        return true;
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> current;
        dfs(ans, current, s, 0);
        return ans;
    }
};
