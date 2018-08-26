class Solution {
public:
    bool is_palindrome(string& s, int l, int r) {
        while (l <= r) {
            if (s[l++] != s[r--]) {
                return false;
            }
        }
        return true;
    }
    vector<vector<string>> partition(string& s, int l, int r) {
        if (l > r) {
            return {};
        } else if (l == r) {
            return {{s.substr(l, 1)}};
        }
        vector<vector<string>> ans;
        for (int i = l; i <= r; i++) {
            if (is_palindrome(s, l, i)) {
                string first = s.substr(l, i - l + 1);
                vector<vector<string>> second = partition(s, i + 1, r);
                for (auto& x : second) {
                    x.push_back(first);
                    ans.push_back(x);
                }
                if (second.size() == 0) {
                    ans.push_back({first});
                }
            }
        }
        return ans;
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans = partition(s, 0, s.length() - 1);
        for (auto& x : ans) {
            reverse(x.begin(), x.end());
        }
        return ans;
    }
};
