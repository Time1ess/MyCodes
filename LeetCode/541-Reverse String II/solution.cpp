// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 16:39
// Last modified: 2017-03-12 16:39
// Filename: solution.cpp
// Description:
class Solution {
public:
    string reverseStr(string s, int k) {
        int len = s.length();
        int start, end;
        for(int i = 0; i < len; i += 2*k)
        {
            start = i;
            if(len - start >= k)
                end = start + k - 1;
            else
                end = len - 1;
            while(start < end)
            {
                swap(s[start], s[end]);
                start++;end--;
            }
        }
        return s;
    }
};
