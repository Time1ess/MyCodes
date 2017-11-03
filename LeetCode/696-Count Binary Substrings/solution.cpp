class Solution {
public:
    int countBinarySubstrings(string s) {
        int cnt = 0, len = s.length();
        for(int i = 0; i < len - 1; i++)
        {
            int k = i;
            int j = i + 1;
            if(s[k] == s[j])
                continue;
            while(k >= 0 && j < len)
            {
                cnt++, k--, j++;
                if(k < 0 || j == len || s[k] != s[k+1] || s[j] != s[j-1])
                    break;
            }
        }
        return cnt;
    }
};
