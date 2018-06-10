class Solution {
public:
    /**
     * @param s: the given string
     * @return: all the possible states of the string after one valid move
     */
    vector<string> generatePossibleNextMoves(string &s) {
        // write your code here
        vector<string> ans;
        int n = s.length();
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i+1] && s[i] == '+') {
                string tmp = s;
                tmp[i] = tmp[i+1] = '-';
                ans.push_back(tmp);
            }
        }
        return ans;
    }
};
