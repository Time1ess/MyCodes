class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> ss;
        int n = s.length();
        for(int i = 0; i < n; i++)
            if(s[i] == '(' || ss.empty() || s[ss.top()] != '(')
                ss.push(i);
            else
                ss.pop();
        if(ss.empty())
            return n;
        int ans = 0;
        int a = n, b = 0;
        while(!ss.empty())
        {
            b = ss.top();
            ss.pop();
            ans = max(ans, a - b - 1);
            a = b;
        }
        ans = max(ans, a);
        return ans;
    }
};
