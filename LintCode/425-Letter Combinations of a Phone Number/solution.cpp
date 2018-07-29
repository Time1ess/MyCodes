class Solution {
public:
    void backtrack(string& digits, vector<string>& ans,
                   vector<string>& chars, string s, int idx, int n) {
        if(idx == n) {
            ans.push_back(s);
            return;
        }
        for(auto c: chars[digits[idx]-'0']) {
            backtrack(digits, ans, chars, s + c, idx + 1, n);
        }
    }
    /**
     * @param digits: A digital string
     * @return: all posible letter combinations
     */
    vector<string> letterCombinations(string &digits) {
        // write your code here
        if(digits.length() == 0) {
            return {};
        }
        vector<string> chars = {
            "", "", "abc", "def", "ghi", "jkl", "mno",
            "pqrs", "tuv", "wxyz",
        };
        vector<string> ans;
        int n = digits.size();
        backtrack(digits, ans, chars, "", 0, n);
        return ans;
    }
};
