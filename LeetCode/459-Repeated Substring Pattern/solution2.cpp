// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 10:50
// Last modified: 2017-03-29 10:50
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        /*
         * This idea based on follows:
         * if S = SpSp, where S is the original string,
         * and Sp is the repeated pattern.
         * if S1 = S + S = SpSpSpSp, if we destroy the pattern
         * in first end last Sp, then we get
         * S2 = SxSpSpSy, if S has a repeated pattern, then S2
         * should have a valid S in it.
        */
        if(s.length() == 0)
            return false;
        string ss = s+s;
        return ss.substr(1, ss.length()-2).find(s) != -1;
    }
};
