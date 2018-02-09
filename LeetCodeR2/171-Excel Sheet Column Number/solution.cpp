class Solution {
public:
    int titleToNumber(string s) {
        int ans = 0;
        int length = s.length();
        for(int i = 0; i < length; i++)
            ans = 26 * ans + (s[i] - 'A' + 1);
        return ans;
    }
};
