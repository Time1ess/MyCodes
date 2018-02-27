class Solution {
public:
    void backtrack(vector<string> &ans, unordered_map<char, string> &digit_to_letters, string &digits, string current, int idx)
    {
        int n = digits.size();
        if(idx == n)
        {
            ans.push_back(current);
            return;
        }
        for(auto c: digit_to_letters[digits[idx]])
            backtrack(ans, digit_to_letters, digits, current + c, idx+1);
    }
    vector<string> letterCombinations(string digits) {
        unordered_map<char, string> digit_to_letters{
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        vector<string> ans;
        if(digits.length() == 0)
            return ans;
        backtrack(ans, digit_to_letters, digits, "", 0);
        return ans;
    }
};
