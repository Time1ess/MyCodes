class Solution {
public:
    void backtrack(vector<string> &ans, string current, int left, int right)
    {
        if(left == 0 && right == 0)
            ans.push_back(current);
        else if(left == 0)
            backtrack(ans, current+")", left, right-1);
        else
        {
            backtrack(ans, current+"(", left-1, right+1);
            if(right > 0)
                backtrack(ans, current+")", left, right-1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        if(n == 0)
            return ans;
        backtrack(ans, "", n, 0);
        return ans;
    }
};
