// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 15:02
// Last modified: 2017-03-12 15:02
// Filename: solution.cpp
// Description:
class Solution {
public:
    int characterReplacement(string s, int k) {
        int len = s.length();
        int maxlen = 0;
        int start = 0;
        int max_count = 0;  // The num of the most frequent char in s[start, end]
        int counts[26] = {0};
        for(int end = 0; end < len; end++)
        {
            max_count = max(max_count, ++counts[s[end] - 'A']);
            while(end - start + 1 - max_count > k)
            {
                counts[s[start] - 'A']--;
                start++;
            }
            maxlen = max(maxlen, end - start + 1);
        }
        return maxlen;
    }
};
