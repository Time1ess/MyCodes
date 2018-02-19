class Solution {
public:
    string longestPalindrome(string s) {
        if(s.length() <= 1)
            return s;
        vector<char> vs;
        for(auto c: s)
        {
            vs.push_back('#');
            vs.push_back(c);
        }
        vs.push_back('#');
        int max_right = 0, pos = 0;
        int n = vs.size();
        vector<int> rl(n, 0);
        int max_pos = 0, max_rl = 0;
        for(int i = 0; i < n; i++)
        {
            if(i < max_right)
                rl[i] = min(rl[2 * pos - i], max_right - i);
            else
                rl[i] = 1;
            while(i - rl[i] >= 0 && i + rl[i] < n && vs[i - rl[i]] == vs[i + rl[i]])
                rl[i]++;
            if(rl[i] + i - 1 > max_right)
            {
                max_right = rl[i] + i - 1;
                pos = i;
            }
            if(rl[i] > max_rl)
            {
                max_rl = rl[i];
                max_pos = i;
            }
        }
        string ans = "";
        for(int i = max_pos - rl[max_pos] + 1; i <= max_pos + rl[max_pos] - 1; i++)
            if(vs[i] != '#')
                ans.push_back(vs[i]);
        return ans;
    }
};
