class Solution {
public:
    /**
     * @param s: a string which consists of lowercase or uppercase letters
     * @return: the length of the longest palindromes that can be built
     */
    int longestPalindrome(string &s) {
        // write your code here
        int cnts[256] = {0};
        for(auto c: s)
            cnts[c]++;
        int length = 0;
        bool hasOdd = false;
        for(auto x: cnts)
            if(x % 2 == 0)
                length += x;
            else {
                length += x - 1;
                hasOdd = true;
            }
        return length + (hasOdd ? 1 : 0);
    }
};
