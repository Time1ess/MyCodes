class Solution {
public:
    bool isMatch(string& s, int i, int m, string& p, int j, int n) {
        if (i == m && j + 2 <= n && p[j+1] == '*') {
            return isMatch(s, i, m, p, j + 2, n);
        } else if (i == m && j == n ) {
            return true;
        } else if (i == m || j == n) {
            return false;
        }
        if (j + 1 == n) {  // REG has no more char
            return (s[i] == p[j] || p[j] == '.') && isMatch(s, i + 1, m, p, j + 1, n);
        }
        if (p[j] == '.' || s[i] == p[j]) {
            // Match
            if (p[j+1] == '*') {
                return isMatch(s, i, m, p, j + 2, n)  // skip match
                    || isMatch(s, i+1, m, p, j, n);  // match one, reg no forward
            }
            return isMatch(s, i + 1, m, p, j + 1, n);
        } else if (p[j+1] == '*') {
            // No match, but can skip
            return isMatch(s, i, m, p, j + 2, n);
        }
        // No match, no skip, fail
        return false;
    }
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        return isMatch(s, 0, m, p, 0, n);
    }
};
