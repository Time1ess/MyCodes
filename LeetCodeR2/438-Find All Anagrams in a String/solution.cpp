class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.length(), m = p.length();
        vector<int> ans;
        if(n < m)
            return ans;
        unordered_map<char, int> cnts;
        for(int i = 0; i < 26; i++)
            cnts['a'+i] = 0;
        for(int i = 0; i < m; i++)
        {
            cnts[s[i]]++;
            cnts[p[i]]--;
        }
        int match_cnt = 0;
        for(auto it: cnts)
            if(it.second == 0)
                match_cnt++;
        if(match_cnt == 26)
            ans.push_back(0);
        for(int i = m; i < n; i++)
        {
            if(s[i] != s[i-m])
            {
                cnts[s[i]]++;
                cnts[s[i-m]]--;
                if(cnts[s[i]] == 0)
                    match_cnt++;
                else if(cnts[s[i]] == 1)
                    match_cnt--;
                if(cnts[s[i-m]] == 0)
                    match_cnt++;
                else if(cnts[s[i-m]] == -1)
                    match_cnt--;
            }
            if(match_cnt == 26)
                ans.push_back(i - m + 1);
        }
        return ans;
    }
};
