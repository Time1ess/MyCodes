class Solution {
public:
    /**
     * @param S: a string
     * @param words: a dictionary of words
     * @return: the number of words[i] that is a subsequence of S
     */
    bool isSubsequence(const string& S,
                       const vector<vector<int>>& nexts, const string& s) {
        int n = s.length();
        int m = S.length();
        int j = 0;
        for(int i = 0; i < n; i++) {
            if(j == m) {
                return false;
            } else if(S[j] == s[i]) {
                j++;
                continue;
            }
            if(nexts[j][s[i]-'a'] == -1) {
                return false;
            }
            j = nexts[j][s[i]-'a'] + 1;
        }
        return true;
    }
    int numMatchingSubseq(string &S, vector<string> &words) {
        // Write your code here
        int n = S.length();
        vector<vector<int>> nexts(n, vector<int>(26, -1));
        vector<int> nearest_chars(26, -1);
        for(int i = n - 1; i >= 0; i--) {
            nexts[i] = nearest_chars;
            nearest_chars[S[i]-'a'] = i;
        }
        int ans = 0;
        for(auto s: words) {
            if(isSubsequence(S, nexts, s)) {
                ans++;
            }
        }
        return ans;
    }
};
