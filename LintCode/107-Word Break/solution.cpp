class Solution {
public:
    /*
     * @param s: A string
     * @param dict: A dictionary of words dict
     * @return: A boolean
     */
    bool wordBreak(string &s, unordered_set<string> &dict) {
        // write your code here
        int n = s.length();
        vector<bool> dp(n + 1, false);
        int max_word_length = 0;
        for (const string& word: dict)
            max_word_length = max(max_word_length, int(word.length()));
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = max(0, i - max_word_length); j < i; j++) {
                if (dp[j] == false)
                    continue;
                const string second_s = s.substr(j, i - j);
                if (dict.find(second_s) != dict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
