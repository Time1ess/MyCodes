class Solution {
public:
    /**
     * @param s: a string
     * @return: return a boolean
     */
    bool repeatedSubstringPattern(string &s) {
        // write your code here
        int n = s.length();
        for (int len = 1; len <= n / 2; len++) {
            int j = 0;
            int i = 0;
            while (i < n) {
                if (s[i] != s[j])
                    break;
                i++;
                j = (j + 1) % len;                
            }
            if (i == n)
                return true;
        }
        return false;
    }
};
