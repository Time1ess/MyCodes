class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string longest = "";
        int n = s.length();
        for(auto ss: d)
        {
            int m = ss.length();
            if(m < longest.length())
                continue;
            int i = 0;
            for(int j = 0; i < m && j < n; j++)
                if(ss[i] == s[j])
                    i++;
            if(i == m && (longest.length() < m || (longest.length() == m && longest > ss)))
               longest = ss;
        }
        return longest;
    }
};
