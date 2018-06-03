class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        string word;
        unordered_map<string, int> cnts;
        unordered_set<string> banned_words(banned.begin(), banned.end());
        int n = paragraph.length();
        for (int i = 0; i <= n; i++) {
            char ch = i < n ? paragraph[i] : ' ';
            if (ch >= 'A' && ch <= 'Z')
                ch = ch - 'A' + 'a';
            if (ch >= 'a' && ch <= 'z') {
                word.push_back(ch);
            } else {
                if (!word.empty() && banned_words.find(word) == banned_words.end()) {
                    cnts[word]++;
                }
                word = "";
            }
        }
        string ans = "";
        int cnt = 0;
        for (auto p: cnts) {
            if (p.second > cnt) {
                ans = p.first;
                cnt = p.second;
            }
        }
        return ans;
    }
};
