class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        if (n <= 1) {
            return n;
        }
        int ans = 0;
        int l = 0, r = 1;
        unordered_set<char> seen;
        seen.insert(s[0]);
        while (r < n) {
            while (seen.find(s[r]) != seen.end()) {
                seen.erase(s[l++]);
            }
            seen.insert(s[r++]);
            ans = max(ans, r - l);
        }
        return ans;
    }
};
