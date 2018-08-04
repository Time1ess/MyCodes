class Solution {
public:
    void generateParenthesis(vector<string>& ans, string current, int remain_pairs, int open_pairs) {
        if(remain_pairs == 0 && open_pairs == 0) {
            ans.push_back(current);
            return;
        }
        if(remain_pairs > 0) {
            string next = current;
            next.push_back('(');
            generateParenthesis(ans, next, remain_pairs - 1, open_pairs + 1);
        }
        if(open_pairs > 0) {
            string next = current;
            next.push_back(')');
            generateParenthesis(ans, next, remain_pairs, open_pairs - 1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        generateParenthesis(ans, "", n, 0);
        return ans;
    }
};
