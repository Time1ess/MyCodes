class Solution {
public:
    /**
     * @param word: the given word
     * @return: the generalized abbreviations of a word
     */
    void backtrack(string& word, vector<string>& ans, int cnt, int idx, int n) {
        if(cnt == 0) {
            string tmp = "";
            int c = 0;
            for(int i = 0; i < n; i++) {
                if(word[i] == ' ') {
                    c++;
                    continue;
                }
                if(c != 0) {
                    tmp.append(to_string(c));
                    c = 0;
                }
                tmp.push_back(word[i]);
            }
            if(c != 0) {
                tmp.append(to_string(c));
            }
            ans.push_back(tmp);
            return;
        }
        if(n - idx < cnt) {
            return;
        }
        for(int i = idx; i < n; i++) {
            char t = word[i];
            word[i] = ' ';
            backtrack(word, ans, cnt-1, i+1, n);
            word[i] = t;
        }
    }
    vector<string> generateAbbreviations(string &word) {
        // Write your code here
        int n = word.length();
        vector<string> ans;
        for(int replace = 0; replace <= n; replace++) {
            backtrack(word, ans, replace, 0, n);
        }
        return ans;
    }
};
