// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-10 14:03
// Last modified: 2017-05-10 14:03
// Filename: solution.cpp
// Description:
class Solution {
public:
    int longest(string &s, int l, int r, int &k)
    {
        if(r - l < k)
            return 0;
        int cnt[26] = {0};
        for(int i = l; i < r; i++)
            cnt[s[i]-'a']++;
            
        for(int i = 0; i < 26; i++)
        {
            if(cnt[i] > 0 && cnt[i] < k)
            {
                for(int j = l; j < r; j++)
                    if(s[j] == i + 'a')
                    {
                        int left = longest(s, l, j, k);
                        int right = longest(s, j+1, r, k);
                        return max(left, right);
                    }
            }
        }
        return r - l;
    }
    int longestSubstring(string s, int k) {
        return longest(s, 0, s.length(), k);
    }
};
