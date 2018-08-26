class Solution {
public:
    int calculate(string s) {
        int num = 0;
        char op = '+';
        int n = s.length();
        stack<int> vals;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            }
            if (((c < '0' || c > '9') && c != ' ') || i == n - 1) {
                switch (op) {
                    case '-':
                        vals.push(-num);
                        break;
                    case '+':
                        vals.push(num);
                        break;
                    case '*':  {
                        int v = vals.top();
                        vals.pop();
                        vals.push(v * num);
                        break;
                    }
                    case '/': {
                        int v = vals.top();
                        vals.pop();
                        vals.push(v / num);
                        break;
                    }
                }
                op = c;
                num = 0;
            }
        }
        int ans = 0;
        while (!vals.empty()) {
            ans += vals.top();
            vals.pop();
        }
        return ans;
    }
};
