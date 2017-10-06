// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-06 09:40
// Last modified: 2017-10-06 09:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool validPalindrome(string s) {
        int l = -1, r = s.length();
        while(++l < --r)
        {
            if(s[l] != s[r])
                if(is_palindrome(s, l+1, r) || is_palindrome(s, l, r-1))
                    return true;
                else
                    return false;
        }
        return true;
    }
    bool is_palindrome(string &s, int l, int r)
    {
        while(l < r)
            if(s[l++] != s[r--])
                return false;
        return true;
    }
};
