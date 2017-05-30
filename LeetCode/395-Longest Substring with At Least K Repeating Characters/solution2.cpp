// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-10 14:09
// Last modified: 2017-05-10 14:09
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int longestSubstring(string s, int k) {
        int cnt[26] = {0};
        for (int i = 0; i < s.length(); i++)
            cnt[s[i]-'a']++;
        return find(s, 0, s.length(), k, cnt);
    }
    int find(string s, int l, int r, int k, int *cnt) {
        if (r - l < k) return 0;
        int max_len = 0;
        int i = l;
        while(i < r)
        {
            while (i < r and cnt[s[i]-'a'] < k)
                i++;
            int j = i, tmp[26] = {0};
            while (j < r and cnt[s[j]-'a'] >= k)
                tmp[s[j++]-'a']++;
            
            if (i == l && j == r)
                return r - l;
            max_len = max(max_len, find(s, i, j, k, tmp));
            
            i = j;
        }
        return max_len;
    }
};
