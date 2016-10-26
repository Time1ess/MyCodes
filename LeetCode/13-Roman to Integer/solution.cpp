// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-26 10:59
// Last modified: 2016-10-26 10:59
// Filename: solution.cpp
// Description:
class Solution {
public:
    map<char, int> create_romans()
    {
        map<char, int> romans;
        romans['I'] = 1;
        romans['V'] = 5;
        romans['X'] = 10;
        romans['L'] = 50;
        romans['C'] = 100;
        romans['D'] = 500;
        romans['M'] = 1000;
        return romans;
    }
    int romanToInt(string s) {
        if(s.length() == 0)
            return 0;
        map<char, int> romans = create_romans();
        int ans=romans[s[s.length()-1]];
        for(int i=0; i < s.length()-1; i++)
        {
            if(romans[s[i]]<romans[s[i+1]])
                ans -= romans[s[i]];
            else
                ans += romans[s[i]];
        }
        return ans;
    }
};
