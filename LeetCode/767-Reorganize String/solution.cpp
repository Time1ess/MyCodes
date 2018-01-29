class Solution {
public:
    string reorganizeString(string S) {
        int n = S.length();
        vector<int> chars(26, 0);
        vector<pair<int, char>> char_counts;
        for(int i = 0; i < n; i++)
        {
            chars[S[i] - 'a']++;
            if(chars[S[i] - 'a'] > (n+1) / 2)
                return "";
        }
        for(int i = 0; i < 26; i++)
            char_counts.push_back({chars[i], i + 'a'});
        sort(char_counts.begin(), char_counts.end(), greater<pair<int, char>>());
        string s = "";
        for(auto x: char_counts)
            s += string(x.first, x.second);
        string ans = "";
        for(int i = 0, j = (n-1) / 2 + 1; i <= (n-1) / 2; i++, j++)
        {
            ans.push_back(s[i]);
            if(j < n)
                ans.push_back(s[j]);
        }
        return ans;
    }
};
