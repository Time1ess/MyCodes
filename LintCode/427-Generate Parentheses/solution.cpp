class Solution {
public:
    /*
     * @param n: n pairs
     * @return: All combinations of well-formed parentheses
     */
    void generate(vector<string> &ans, string current, int n, int c)
    {
        // if left > 0, then can append right parenthese
        if(n == 0 && c == 0)
        {
            ans.push_back(current);
            return;
        }
        if(n > 0)
        {
            string new_current = current;
            new_current.push_back('(');
            generate(ans, new_current, n-1, c+1);
        }
        if(c > 0)
        {
            string new_current = current;
            new_current.push_back(')');
            generate(ans, new_current, n, c-1);
        }
    }
    vector<string> generateParenthesis(int n) {
        // write your code here
        vector<string> ans;
        generate(ans, "", n, 0);
        return ans;
    }
};
