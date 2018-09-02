class Solution {
public:
    int scoreOfParentheses(string S) {
        int depth = 0;
        int ans = 0;
        int n = S.length();
        for (int i = 0; i < n - 1; i++) {
            if (S[i] == '(') {
                depth++;
            } else {
                depth--;
            }
            if (S[i] == '(' && S[i+1] == ')') {
                ans += 1 << (depth - 1);
            }
        }
        return ans;
    }
};
