class Solution {
public:
    int extend_palindrome(string &s, int l, int r)
    {
        int cnt = 0;
        int n = s.length();
        while(l >= 0 && r < n && s[l--] == s[r++])
            cnt++;
        return cnt;
    }
    int countSubstrings(string s) {
        int ans = 0;
        for(int i = 0; i < s.length(); i++)
        {
            ans += extend_palindrome(s, i, i);
            ans += extend_palindrome(s, i, i+1);
        }
        return ans;
    }
};
