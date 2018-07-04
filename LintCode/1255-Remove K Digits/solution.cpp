class Solution {
public:
    /**
     * @param num: a string
     * @param k: an integer
     * @return: return a string
     */
    string removeKdigits(string &num, int k) {
        // write your code here
        int n = num.size();
        int cnt = n - k;
        if(n <= k)
            return "0";
        stack<char> s;
        for(int i = 0; i < n; i++) {
            while(!s.empty() && k > 0 && s.top() > num[i]) {
                s.pop();
                k--;
            }
            s.push(num[i]);
        }
        string ans = "";
        while(!s.empty()) {
            ans.push_back(s.top());
            s.pop();
        }
        reverse(ans.begin(), ans.end());
        int leading_zero_idx = 0;
        int len = ans.length();
        while(leading_zero_idx < len && ans[leading_zero_idx] == '0') {
            leading_zero_idx++;
        }
        return leading_zero_idx == len ? "0" : ans.substr(leading_zero_idx, cnt);
    }
};
