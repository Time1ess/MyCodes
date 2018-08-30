class Solution {
public:
    bool bijectionInternal(const string& a, const string& b) {
        int n = a.length();
        int m = b.length();
        if (n != m) {
            return false;
        }
        vector<char> mapping(128, 0);
        for (int i = 0; i < n; i++) {
            if (mapping[a[i]] != 0) {
                if (mapping[a[i]] != b[i]) {
                    return false;
                }
            } else {
                mapping[a[i]] = b[i];
            }
        }
        return true;
    }
    bool bijection(const string& a, const string& b) {
        return bijectionInternal(a, b) && bijectionInternal(b, a);
    }
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> ans;
        for (const string& word : words) {
            if (bijection(word, pattern)) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};
