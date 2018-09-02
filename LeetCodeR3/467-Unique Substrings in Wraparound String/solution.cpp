class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int n = p.length();
        int max_length = 0;
        vector<int> cnt(26, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0 && ((p[i] - p[i-1]) == 1 || (p[i] - p[i-1] == -25))) {
                max_length++;
            } else {
                max_length = 1;
            }
            cnt[p[i]-'a'] = max(cnt[p[i]-'a'], max_length);
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            ans += cnt[i];
        }
        return ans;
    }
};
