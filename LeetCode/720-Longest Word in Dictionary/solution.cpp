class Solution {
public:
    bool can_built(unordered_set<string> &ss, string &s)
    {
        string sub_s = s.substr(0, s.length()-1);
        if(sub_s.length() == 0 || (ss.find(sub_s) != ss.end() && can_built(ss, sub_s)))
            return true;
        return false;
    }
    string longestWord(vector<string>& words) {
        unordered_set<string> ss;
        for(auto x: words)
            ss.insert(x);
        string ans = "";
        for(auto x: words)
            if(can_built(ss, x) && (x.length() > ans.length() || (x.length() == ans.length() && x < ans)))
                ans = x;
        return ans;
    }
};
