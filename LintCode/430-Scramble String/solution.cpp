class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: Another string
     * @return: whether s2 is a scrambled string of s1
     */
    bool isScramble(string &s1, string &s2, int l1, int r1, int l2, int r2)
    {
        // Partition s1 and s2 into two parts, whose chars cnt are the same.
        // check substr isScramble
        if(l1 == r1)
            return s1[l1] == s2[l2];
        bool ans = false;
        for(int i = l1; i < r1; i++)
        {
            int len = i - l1 + 1;
            ans = ans || (
                isScramble(s1, s2, l1, l1 + len - 1, l2, l2 + len - 1)
                && isScramble(s1, s2, l1 + len, r1, l2 + len, r2));
            ans = ans || (
                isScramble(s1, s2, l1, l1 + len - 1, r2 - len + 1, r2)
                && isScramble(s1, s2, l1 + len, r1, l2, l2 + len - 1));
            if(ans)
                break;
        }
        return ans;
    }
    bool isScramble(string &s1, string &s2) {
        // write your code here
        if(s1.length() != s2.length())
            return false;
        int len = s1.length();
        return isScramble(s1, s2, 0, len - 1, 0, len - 1);
    }
};
