class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int cnt = 0;
        int n_g = g.size(), n_s = s.size();
        if(n_g == 0 || n_s == 0)
            return cnt;
        int i = 0, j = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        while(i < n_g && j < n_s)
        {
            if(g[i] <= s[j])
            {
                cnt++;
                i++;
            }
            j++;
        }
        return cnt;
    }
};
