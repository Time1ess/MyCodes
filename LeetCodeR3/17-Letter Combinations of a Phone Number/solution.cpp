class Solution {
public:
    void generate_combinations(const string& digits, unordered_map<char, string>& phone, vector<string>& ans,
                               string cur, int idx, int n) {
        if (idx == n) {
            ans.push_back(cur);
            return;
        }
        for (auto ch: phone[digits[idx]]) {
            string tmp = cur;
            tmp.push_back(ch);
            generate_combinations(digits, phone, ans, tmp, idx + 1, n);
        }
    }
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        if (n == 0) {
            return {};
        }
        unordered_map<char, string> phone = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"},
        };
        vector<string> ans;
        generate_combinations(digits, phone, ans, "", 0, n);
        return ans;
    }
};
