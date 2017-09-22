// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-22 09:14
// Last modified: 2017-09-22 09:14
// Filename: solution.cpp
// Description:
class Solution {
public:
    int lengthOfLastWord(string s) {
        int end = s.length() - 1;
        if(end == -1)
            return 0;
        while(end >= 0 && s[end] == ' ')
            end--;  // end: last char index
        int start = end;
        while(start >= 0 && s[start] != ' ')
            start --;
        return end - start;
    }
};
