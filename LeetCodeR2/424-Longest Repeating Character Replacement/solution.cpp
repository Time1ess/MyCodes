class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.length();
        int ans = 0;
        vector<int> cnts(26, 0);
        int start = 0;
        int max_count = 0;
        for(int end = 0; end < n; end++)
        {
            max_count = max(max_count, ++cnts[s[end] - 'A']);
            while(end - start + 1 - max_count > k)
            {
                cnts[s[start]-'A']--;
                start++;
            }
            ans = max(ans, end - start + 1);
        }
        return ans;
    }
};
