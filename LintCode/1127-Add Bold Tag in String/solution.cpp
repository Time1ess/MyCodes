class Solution {
public:
    /**
     * @param s: a string
     * @param dict: a list of strings
     * @return: return a string
     */
    string addBoldTag(string &s, vector<string> &dict) {
        // write your code here
        int n = s.length();
        int end = 0;
        vector<bool> bold(n, false);
        for(int i = 0; i < n; i++) {
            for(auto word: dict) {
                int m = word.length();
                if(i + m <= n && s.substr(i, m) == word)
                    end = max(end, i + m);
            }
            bold[i] = end > i;
        }
        string ans = "";
        for(int i = 0; i < n; i++) {
            if(!bold[i]) {
                ans.push_back(s[i]);
                continue;
            }
            int j = i;
            while(j < n && bold[j])
                j++;
            ans.append("<b>" + s.substr(i, j - i) + "</b>");
            i = j - 1;
        }
        return ans;
    }
};
