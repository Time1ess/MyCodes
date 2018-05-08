class Solution {
public:
    /**
     * @param A: A string
     * @param B: A string
     * @return: if string A contains all of the characters in B return true else return false
     */
    bool compareStrings(string &A, string &B) {
        // write your code here
        int cnt[26] = {0};
        for(auto c: A)
            cnt[c - 'A']++;
        for(auto c: B)
            cnt[c - 'A']--;
        for(int i = 0; i < 26; i++)
            if(cnt[i] < 0)
                return false;
        return true;
    }
};
