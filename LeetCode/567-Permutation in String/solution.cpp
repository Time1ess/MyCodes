// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-01 15:17
// Last modified: 2017-05-01 15:17
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int size1 = s1.length(), size2 = s2.length();
        if(size1 > size2)
            return false;
        int cnt[26] = {0};
        for(int i = 0; i < size1; i++)
        {
            cnt[s1[i] - 'a']++;
            cnt[s2[i] - 'a']--;
        }
        int remain = 0;
        for(int i = 0; i < 26; i++)
            remain += cnt[i] != 0 ? 1 : 0;
        if(remain == 0)
            return true;
        for(int r = size1; r < size2; r++)
        {
            cnt[s2[r-size1] - 'a']++;
            if(cnt[s2[r-size1] - 'a'] == 0)
                remain--;
            else if(cnt[s2[r-size1] - 'a'] == 1)
                remain++;

            cnt[s2[r] - 'a']--;
            if(cnt[s2[r] - 'a'] == 0)
                remain--;
            else if(cnt[s2[r] - 'a'] == -1)
                remain++;
            if(remain == 0)
                return true;
        }
        return false;
    }
};
