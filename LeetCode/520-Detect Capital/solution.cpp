// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-21 15:57
// Last modified: 2017-02-21 15:57
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool detectCapitalUse(string word) {
        int upper=0, lower=0;
        for(char c:word)
        {
            if(c >= 'A' && c <= 'Z')
                upper++;
            else if(c >= 'a' && c <= 'z')
                lower++;
        }
        if((upper&&!lower)||(!upper&&lower)||(upper==1&&word[0] >= 'A'&&word[0] <='Z'))
            return true;
        return false;
    }
};
