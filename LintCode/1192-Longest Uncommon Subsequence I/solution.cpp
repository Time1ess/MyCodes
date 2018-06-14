class Solution {
public:
    /**
     * @param a: a string
     * @param b: a string
     * @return: return a integer
     */
    int findLUSlength(string &a, string &b) {
        // write your code here
        int n = a.length();
        int m = b.length();
        return a == b ? -1 : max(m, n);
    }
};
