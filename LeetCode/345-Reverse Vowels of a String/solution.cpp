// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-02 08:47
// Last modified: 2017-04-02 08:47
// Filename: solution.cpp
// Description:
class Solution {
public:
    string reverseVowels(string s) {
        int len = s.length();
        int i = 0, j = len - 1;
        int vowel[256] = {0};
        vowel['a'] = vowel['e'] = vowel['i'] = vowel['o'] = vowel['u'] = 1;
        vowel['A'] = vowel['E'] = vowel['I'] = vowel['O'] = vowel['U'] = 1;
        while(i < j)
        {
            while(i < len && !vowel[s[i]])i++;
            while(j >= 0 && !vowel[s[j]])j--;
            if(i < j)
                swap(s[i++], s[j--]);
        }
        return s;
    }
};
