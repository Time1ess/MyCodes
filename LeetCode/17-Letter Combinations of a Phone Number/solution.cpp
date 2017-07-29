// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-29 11:28
// Last modified: 2017-07-29 11:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    void combine_letters(string &digits, const vector<string> &mappings, vector<string> &ans, string s, int idx, int len)
    {
        if(idx == len)
        {
            ans.push_back(s);
            return;
        }
        const string &ts = mappings[digits[idx] - '2'];
        for(int i = 0; i < ts.length(); i++)
            combine_letters(digits, mappings, ans, s+ts[i], idx+1, len);
    }
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        if(digits == "")
            return ans;
        const static vector<string> mappings = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        combine_letters(digits, mappings, ans, "", 0, digits.length());
        return ans;
    }
};
