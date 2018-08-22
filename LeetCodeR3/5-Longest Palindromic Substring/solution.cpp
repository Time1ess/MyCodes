class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) {
            return s;
        }
        vector<char> ss;
        ss.push_back('^');
        ss.push_back('#');
        for (auto c: s) {
            ss.push_back(c);
            ss.push_back('#');
        }
        ss.push_back('$');
        int right_most = 0;
        int ref = 0;
        int m = ss.size();
        vector<int> radius(m, 0);
        string ans = "";
        for (int i = 1; i < m - 1; i++) {
            if (i < right_most) {
                radius[i] = min(radius[2 * ref - i], right_most - i);
            } else {
                radius[i] = 1;
            }
            while (ss[i-radius[i]] == ss[i+radius[i]]) {
                radius[i]++;
            }
            if (right_most < i + radius[i]) {
                ref = i;
                right_most = i + radius[i];
            }
            int new_len = (2 * radius[i] - 1) / 2;
            if (new_len > ans.length()) {
                string new_ans = "";
                for (int j = i - radius[i] + 1; j < i + radius[i]; j++) {
                    if (ss[j] != '#') {
                        new_ans.push_back(ss[j]);
                    }
                }
                ans = new_ans;
            }
        }
        return ans;
    }
};
