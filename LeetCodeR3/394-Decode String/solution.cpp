class Solution {
public:
    int read_repeat(const string& s, int& idx, int n) {
        int repeat = 0;
        while(idx < n && s[idx] != '[') {
            repeat = repeat * 10 + s[idx++] - '0';
        }
        return repeat;
    }
    string decodeString(const string& s, int& idx, int n) {
        if(idx == n) {
            return "";
        }
        string ans = "";
        while(idx < n && s[idx] != ']') {
            if(s[idx] >= '0' && s[idx] <= '9') {
                int repeat = read_repeat(s, idx, n);
                // Meet [
                idx++;
                string child = decodeString(s, idx, n);
                // Meet ]
                idx++;
                for(int i = 0; i < repeat; i++) {
                    ans.append(child);
                }
            } else {
                ans.push_back(s[idx++]);
            }
        }
        return ans;
    }
    string decodeString(string s) {
        int n = s.length();
        int idx = 0;
        return decodeString(s, idx, n);
    }
};
