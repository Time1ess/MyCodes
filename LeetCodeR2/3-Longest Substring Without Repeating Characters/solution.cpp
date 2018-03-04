class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool exists[256] = {false};
        int ans = 0;
        int j = 0;
        for(int i = 0; i < s.length(); i++)
        {
            while(j <= i && exists[s[i]])
                exists[s[j++]] = false;
            exists[s[i]] = true;
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
