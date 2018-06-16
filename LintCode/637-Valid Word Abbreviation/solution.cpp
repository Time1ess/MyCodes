class Solution {
public:
    /**
     * @param word: a non-empty string
     * @param abbr: an abbreviation
     * @return: true if string matches with the given abbr or false
     */
    int parseInt(const string& abbr, const int m, int& j) {
        int ans = 0;
        while(j < m && abbr[j] >= '0' && abbr[j] <= '9') {
            ans = ans * 10 + abbr[j] - '0';
            j++;
        }
        return ans;
    }
    bool validWordAbbreviation(string &word, string &abbr) {
        // write your code here
        int n = word.length();
        int m = abbr.length();
        int j = 0;
        int starCnt = 0;
        for(int i = 0; i < n; i++) {
            if(starCnt != 0) {
                starCnt--;
            } else if(j < m && word[i] == abbr[j]) {
                j++;
            } else if(j < m && abbr[j] >= '1' && abbr[j] <= '9') {
                starCnt = parseInt(abbr, m, j);
                if(starCnt == 0)
                    return false;
                starCnt--;
            } else {
                return false;
            }
        }
        return starCnt == 0;
    }
};
