class Solution {
public:
    bool isSubsequence(string s, string t) {
        unordered_map<char, vector<int>> indices;
        int n = s.length(), m = t.length();
        for(int i = 0; i < m; i++)
            indices[t[i]].push_back(i);
        int start_idx = 0;
        for(int i = 0;i < n; i++)
        {
            auto it = lower_bound(indices[s[i]].begin(), indices[s[i]].end(), start_idx);
            if(it == indices[s[i]].end())
                return false;
            start_idx = *it + 1;
        }
        return true;
    }
};
