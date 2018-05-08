class Solution {
public:
    /**
     * @param s: The first string
     * @param t: The second string
     * @return: true or false
     */
    bool anagram(string &s, string &t) {
        // write your code here
        int cnts[256] = {0};
        for(auto c: s)
            cnts[c]++;
        for(auto c: t)
            cnts[c]--;
        for(int i = 0; i < 256; i++)
            if(cnts[i] != 0)
                return false;
        return true;
    }
};
