class Solution {
public:
    /*
     * @param s: a string
     * @param p: a string
     * @return: a list of index
     */
    vector<int> findAnagrams(string &s, string &p) {
        // write your code here
        int full_match = 0;
        int m = s.length(), n = p.length();
        vector<int> sliding_window(26, 0);
        for(int i = 0; i < n; i++)
            sliding_window[p[i] - 'a']++;
        for(int i = 0; i < 26; i++)
            full_match += sliding_window[i] == 0 ? 1 : 0;
        vector<int> ans;
        for(int i = 0; i < m; i++)
        {
            sliding_window[s[i] - 'a']--;
            if(sliding_window[s[i] - 'a'] == 0)
                full_match++;
            if(i >= n)
            {
                sliding_window[s[i-n] - 'a']++;
                if(sliding_window[s[i-n] - 'a'] == 1)
                    full_match--;
            }
            if(full_match == 26)
                ans.push_back(i - n + 1);
        }
        return ans;
    }
};
