class Solution {
public:
    /**
     * @param str: String
     * @return: String
     */
    string convertPalindrome(string &str) {
        // Write your code here
        int n = str.length();
        string rev = str;
        reverse(rev.begin(), rev.end());
        for(int i = 0; i < n; i++) {
            if(str.substr(0, n - i) == rev.substr(i)) {
                return rev.substr(0, i) + str;
            }
        }
        return "";
    }
};
