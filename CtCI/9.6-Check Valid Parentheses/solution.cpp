class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        // write code here
        stack<char> s;
        for(auto c: A) {
            if (c != '(' && c != ')')
                continue;
            else if(c == '(')
                s.push(c);
            else if(c == ')' && !s.empty() && s.top() == '(') {
                s.pop();
            } else
                return false;
        }
        return s.empty();
    }
};
