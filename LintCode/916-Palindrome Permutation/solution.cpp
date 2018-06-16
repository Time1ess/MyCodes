class Solution {
public:
    /**
     * @param s: the given string
     * @return: if a permutation of the string could form a palindrome
     */
    bool canPermutePalindrome(string &s) {
        // write your code here
        int cnts[256] = {0};
        for(auto c: s)
            cnts[c]++;
        bool hasOdd = false;
        for(auto x: cnts)
            if(x % 2 == 0)
                continue;
            else if(!hasOdd)
                hasOdd = true;
            else
                return false;
        return true;
    }
};
