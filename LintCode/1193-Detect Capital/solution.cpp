class Solution {
public:
    /**
     * @param word: a string
     * @return: return a boolean
     */
    bool isCapital(char c) {
        return c >= 'A' && c <= 'Z';
    }
    bool detectCapitalUse(string &word) {
        // write your code here
        int n = word.length();
        bool allCapital = true;
        bool anyCapital = false;
        bool anyCapitalFromSecond = false;
        for(int i = 0; i < n; i++) {
            bool capital = isCapital(word[i]);
            allCapital = allCapital && capital;
            anyCapital = anyCapital || capital;
            if (i != 0)
                anyCapitalFromSecond = anyCapitalFromSecond || capital;
        }
        return allCapital
               || !anyCapital
               || (n > 1 && isCapital(word[0]) && !anyCapitalFromSecond);
    }
};
