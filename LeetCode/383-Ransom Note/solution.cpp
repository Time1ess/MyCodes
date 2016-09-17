// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 14:12
// Last modified: 2016-09-17 14:12
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int chr_cnt[26];
        memset(chr_cnt, 0, sizeof(chr_cnt));
        for(int i=0; i < magazine.length(); i++)
            chr_cnt[magazine[i]-'a']++;
        for(int i=0; i < ransomNote.length(); i++)
        {
            if(chr_cnt[ransomNote[i]-'a']==0)
                return false;
            chr_cnt[ransomNote[i]-'a']--;
        }
        return true;
    }
};
