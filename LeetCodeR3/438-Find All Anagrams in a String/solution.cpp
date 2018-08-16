class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        vector<int> cnts(26, 0);
        int full_match = 26;
        for (auto c: p) {
            cnts[c-'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (cnts[i] != 0) {
                full_match--;
            }
        }
        int m = p.length();
        int n = s.length();
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            cnts[idx]++;
            if (cnts[idx] == 0) {
                full_match++;
            } else if (cnts[idx] == 1) {
                full_match--;
            }
            if (i >= m) {
                int idx2 = s[i-m] - 'a';
                cnts[idx2]--;
                if (cnts[idx2] == 0) {
                    full_match++;
                } else if (cnts[idx2] == -1) {
                    full_match--;
                }
            }
            if (full_match == 26) {
                ans.push_back(i-m+1);
            }
        }
        return ans;
    }
};
