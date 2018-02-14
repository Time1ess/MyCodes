class Solution {
public:
    int longestPalindrome(string s) {
        int cnts[256] = {0};
        for(auto c: s)
            cnts[c]++;
        int even = 0;
        bool odd = false;
        for(int i = 0; i < 256; i++)
        {
            even += cnts[i] / 2;
            if(cnts[i] & 0x1)
                odd = true;
        }
        return even * 2 + (odd ? 1 : 0);
    }
};
