class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length();
        vector<int> cnts(256, 0);
        int full_match = 256;
        for (auto c: t) {
            cnts[c]--;
            if (cnts[c] == -1) {
                full_match--;
            }
        }
        // Find first string to cover t
        int j = 0;
        while (j < n && full_match != 256) {
            cnts[s[j]]++;
            if (cnts[s[j]] == 0) {
                full_match++;
            }
            j++;
        }
        // No answer
        if (full_match != 256) {
            return "";
        }
        int ans_i = 0, ans_j = j;
        // Try to minimize the range
        int i = 0;
        j--;
        while (j < n) {
            while (cnts[s[i]] > 0) {
                cnts[s[i]]--;
                i++;
            }
            if ((j - i) < (ans_j - ans_i)) {
                ans_i = i;
                ans_j = j;
            }
            // Critical character
            // before we move forward i, we need to move forward j to add one more char i
            j++;
            if (j == n) {
                break;
            }
            cnts[s[j]]++;
        }
        return s.substr(ans_i, ans_j - ans_i + 1);
    }
};
