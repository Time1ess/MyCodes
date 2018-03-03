class Solution {
public:
    bool isValid(string s) {
        stack<char> ps;
        int n = s.length();
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[')
                ps.push(s[i]);
            else
            {
                if(ps.empty())
                    return false;
                char top = ps.top();
                if((s[i] == ')' && top == '(') || (s[i] == ']' && top == '[') || (s[i] == '}' && top == '{'))
                    ps.pop();
                else
                    return false;
            }
        }
        return ps.empty();
    }
};
