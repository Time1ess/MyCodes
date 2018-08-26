class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> vals;
        stack<char> ops;
        for (auto x: tokens) {
            if (x == "*" || x == "/") {
                int v2 = vals.top();
                vals.pop();
                int v1 = vals.top();
                vals.pop();
                vals.push(x == "*" ? (v1 * v2) : (v1 / v2));
            } else if (x == "+" || x == "-") {
                int v2 = vals.top();
                vals.pop();
                int v1 = vals.top();
                vals.pop();
                vals.push(x == "+" ? (v1 + v2) : (v1 - v2));
            } else {
                vals.push(stoi(x));
            }
        }
        return vals.top();
    }
};
