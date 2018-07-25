class Solution {
public:
    /**
     * @param str: String
     * @return: String
     */
    string convertPalindrome(string &str) {
        int n = str.length();
        string rev = str;
        reverse(rev.begin(), rev.end());
        string snew = str + "#" + rev;
        int len = snew.length();        
        vector<int> next(len, 0);
        for(int i = 1; i < len; i++) {
            int t = next[i-1];
            while(t > 0 && snew[i] != snew[t]) {
                t = next[t-1];
            }
            if(snew[i] == snew[t]) {
                t++;
            }
            next[i] = t;
        }
        return rev.substr(0, n - next[len-1]) + str;
    }
};
