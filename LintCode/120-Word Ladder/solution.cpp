class Solution {
public:
    /*
     * @param start: a string
     * @param end: a string
     * @param dict: a set of string
     * @return: An integer
     */
    int edit_distance(string &a, string &b)
    {
        int n = a.length();
        int ans = 0;
        for(int i = 0; i < n; i++)
            if(a[i] != b[i])
                ans++;
        return ans;
    }
    int ladderLength(string &start, string &end, unordered_set<string> &dict) {
        // write your code here
        if(start == end)
            return 1;
        int n = start.length();
        queue<pair<string, int>> words;
        words.push({start, 1});
        while(!words.empty())
        {
            auto p = words.front();
            words.pop();
            if(edit_distance(p.first, end) == 1)
                return p.second + 1;
            vector<string> cands;
            for(auto next_word: dict)
                if(edit_distance(next_word, p.first) == 1)
                    cands.push_back(next_word);
            for(auto next_word: cands)
            {
                dict.erase(next_word);
                words.push({next_word, p.second + 1});
            }
        }
        return 0;
    }
};
