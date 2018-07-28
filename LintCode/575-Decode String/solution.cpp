class Solution {
public:
    /**
     * @param s: an expression includes numbers, letters and brackets
     * @return: a string
     */
    int expandNum(const string& str, int& s, int e) {
        if(s >= e) {
            return 0;
        }
        int ans = 0;
        while(s < e && str[s] >= '0' && str[s] <= '9') {
            ans = ans * 10 + (str[s++] - '0');
        }
        return ans;
    }
    string expandString(const string& str, int& s, int e) {
        if(s >= e) {
            return "";
        }
        string ans = "";
        while(s < e && str[s] != ']') {
            if(str[s] >= '0' && str[s] <= '9') {
                int cnt = expandNum(str, s, e);
                // We encounter xxx[yyy], move forward one char
                s++;
                string tmp = expandString(str, s, e);
                for(int i = 0; i < cnt; i++) {
                    ans.append(tmp);
                }
                // End of substring, move forward one char
                s++;
            } else {
                ans.push_back(str[s++]);
            }
        }
        return ans;
    }
    string expressionExpand(string &s) {
        // write your code here
        int i = 0;
        int n = s.length();
        return expandString(s, i, n);
    }
};
