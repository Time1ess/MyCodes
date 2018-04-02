class Solution {
public:
    /**
     * @param s: the given string
     * @return: all the palindromic permutations (without duplicates) of it
     */
    void dfs(vector<string> &ans, string s, vector<pair<char, int>> &evens,
             int k, int mid, pair<char, int> odd)
    {
        if(k == mid)
        {
            if(odd.first != ' ')
                s.push_back(odd.first);
            for(int j = mid - 1; j >= 0; j--)
                s.push_back(s[j]);
            ans.push_back(s);
            return;
        }
        if(odd.second > 1)
        {
            string next_s = s;
            odd.second -= 2;
            next_s.push_back(odd.first);
            dfs(ans, next_s, evens, k + 1, mid, odd);
            odd.second += 2;
        }
        int n = evens.size();
        for(int i = 0; i < n; i++)
        {
            if(evens[i].second == 0)
                continue;
            string next_s = s;
            evens[i].second -= 2;
            next_s.push_back(evens[i].first);
            dfs(ans, next_s, evens, k + 1, mid, odd);
            evens[i].second += 2;
        }
    }
    vector<string> generatePalindromes(string &s) {
        // write your code here
        unordered_map<char, int> cnts;
        for(auto c: s)
            cnts[c]++;
        vector<pair<char, int>> evens;
        pair<char, int> odd;
        odd = {' ', 0};
        int mid = 0;
        for(auto p: cnts)
        {
            if(p.second % 2 == 0)
                evens.push_back(p);
            else if(odd.second == 0)
                odd = p;
            else
                return {};
            mid += p.second / 2;
        }
        int n = evens.size();
        vector<string> ans;
        dfs(ans, "", evens, 0, mid, odd);
        return ans;
    }
};
