// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-09 09:35
// Last modified: 2017-08-09 09:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    void set_bit(int &not_clear, int position, bool on)
    {
        if(on)
            not_clear |= 1<<position;
        else
            not_clear &= ~(1<<position);
    }
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        int s_len = s.length(), p_len = p.length();
        if(s_len < p_len)
            return ans;
        int cnts[26] = {0};
        for(int i = 0; i < p_len; i++)
            cnts[s[i] - 'a']--, cnts[p[i] - 'a']++;
        int not_clear = 0;
        for(int i = 0; i < 26; i++)
            set_bit(not_clear, i, cnts[i] != 0);
        for(int i = p_len; i < s_len; i++)
        {
            if(not_clear == 0)
                ans.push_back(i - p_len);
            cnts[s[i] - 'a']--, cnts[s[i-p_len] - 'a']++;
            set_bit(not_clear, s[i] - 'a', cnts[s[i] - 'a'] != 0);
            set_bit(not_clear, s[i-p_len] - 'a', cnts[s[i-p_len] - 'a'] != 0);
        }
        if(not_clear == 0)
            ans.push_back(s_len - p_len);
        return ans;
    }
};
