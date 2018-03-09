bool cmp(const string &a, const string &b)
{
    return a.length() > b.length() || (a.length() == b.length() && a < b);
}

class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), cmp);
        string ans = "";
        set<string> cands;
        for(auto x: words)
            cands.insert(x);
        for(auto x: words)
        {
            if(x.length() <= ans.length())
                break;
            string tmp = x;
            tmp.pop_back();
            bool found = true;
            while(tmp.length() != 0)
            {
                if(cands.find(tmp) == cands.end())
                {
                    found = false;
                    break;
                }
                tmp.pop_back();
            }
            if(found)
                ans = x;
        }
        return ans;
    }
};
