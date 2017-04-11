// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-11 10:01
// Last modified: 2017-04-11 10:01
// Filename: solution.cpp
// Description:
class Solution {
public:
    string reverseWords(string s) {
        int i, j, size;
        size = s.length();
        if(size == 0)
            return s;
        i = 0;
        for(int k = 0; k < size; k++)
        {
            if(s[k] != ' ')
                continue;
            for(j = k-1; j > i; j--, i++)
                swap(s[i], s[j]);
            i = k+1;
        }
        j = size-1;
        while(i < j)
            swap(s[i++], s[j--]);
        return s;
    }
};
