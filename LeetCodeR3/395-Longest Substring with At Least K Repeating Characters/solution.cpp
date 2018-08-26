class Solution {
public:
    int longestSubstring(string& s, int l, int r, int k) {
        if (l >= r) {
            return 0;
        }
        unordered_map<char, int> cnts;
        for (int i = l; i < r; i++) {
            cnts[s[i]]++;
        }
        int mid = l;
        while (mid < r && cnts[s[mid]] >= k) {
            mid++;
        }
        if (mid == r) {
            return r - l;
        }
        int ans = longestSubstring(s, l, mid, k);
        while (mid < r && cnts[s[mid]] < k) {
            mid++;
        }
        return max(ans, longestSubstring(s, mid, r, k));
    }
    int longestSubstring(string s, int k) {
        return longestSubstring(s, 0, s.length(), k);
    }
};
