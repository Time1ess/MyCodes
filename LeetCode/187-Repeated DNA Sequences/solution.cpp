// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-23 09:56
// Last modified: 2017-09-23 09:56
// Filename: solution.cpp
// Description:
class Solution {
public:
    int map_int(char ch)
    {
        switch(ch)
        {
            case 'A':
                return 0;
            case 'C':
                return 1;
            case 'G':
                return 2;
            case 'T':
                return 3;
        }
    }
    char map_char(int ch_int)
    {
        switch(ch_int)
        {
            case 0:
                return 'A';
            case 1:
                return 'C';
            case 2:
                return 'G';
            case 3:
                return 'T';
        }
    }
    string reverse_int_to_string(int dna)
    {
        string s(10, ' ');
        for(int i = 9; i >= 0; i--)
        {
            s[i] = map_char(dna & 0x3);
            dna >>= 2;
        }
        return s;
    }
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        int length = s.length();
        if(length <= 10)
            return ans;
        unordered_map<int, int> showups;
        const int MASK = 0x000fffff;
        int slide_window = 0;
        for(int i = 0; i < length; i++)
        {
            slide_window = (MASK & (slide_window << 2)) + map_int(s[i]);
            if(i >= 9)
                showups[slide_window]++;
        }
        for(auto x: showups)
            if(x.second > 1)
                ans.push_back(reverse_int_to_string(x.first));
        return ans;
    }
};
