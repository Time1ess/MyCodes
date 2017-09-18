// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-18 08:34
// Last modified: 2017-09-18 08:34
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int max_contiguous[26] = {0};
        int max_cur = 0;
        for(int i = 0; i < p.length(); i++)
        {
            if(i > 0 && ((p[i-1] == 'z' && p[i] == 'a') || p[i] - p[i-1] == 1))
                max_cur ++;
            else
                max_cur = 1;
            max_contiguous[p[i] - 'a'] = max(max_cur, max_contiguous[p[i] - 'a']);
        }
        return accumulate(max_contiguous, max_contiguous+26, 0);
    }
};
