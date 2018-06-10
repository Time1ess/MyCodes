class Solution {
public:
    /**
     * @param s: a string
     * @param t: a string
     * @return: the letter that was added in t
     */
    char findTheDifference(string &s, string &t) {
        return accumulate(t.begin(), t.end(), 0) - accumulate(s.begin(), s.end(), 0);
    }
};
