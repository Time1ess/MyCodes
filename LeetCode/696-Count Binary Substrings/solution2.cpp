class Solution {
public:
    int countBinarySubstrings(string s) {
        int cnt = 0, cur = 1, prev = 0;
        for(int i = 1; i < s.length(); i++)
        {
            if(s[i] == s[i-1])
                cur ++;
            else
            {
                prev = cur;
                cur = 1;
            }
            if(prev >= cur)
                cnt ++;
        }
        return cnt;
    }
};
