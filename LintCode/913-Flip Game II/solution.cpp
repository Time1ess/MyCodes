class Solution {
public:
    /**
     * @param s: the given string
     * @return: if the starting player can guarantee a win
     */
    bool canWin(string &s) {
        // write your code here
        int n = s.length();
        bool win = false;
        for(int i = 0; i < n - 1; i++) {
            if(s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                if(win || !canWin(s)) {
                    win = true;
                }
                s[i] = s[i+1] = '+';
            }
        }
        return win;
    }
};
