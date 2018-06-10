class Solution {
public:
    /**
     * @param s: a string
     * @return: reverse only the vowels of a string
     */
    string reverseVowels(string &S) {
        string ans = S;
        static const unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u',
                                                   'A', 'E', 'I', 'O', 'U'};
        int n = ans.length();
        int s = 0, e = n - 1;
        while (s < e) {
            while (s < e && vowels.find(ans[s]) == vowels.end())
                s++;
            while (s < e && vowels.find(ans[e]) == vowels.end())
                e--;
            if (s < e) {
                swap(ans[s], ans[e]);
                s++;
                e--;
            }
        }
        return ans;
    }
};
