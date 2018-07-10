bool cmp(const string& a, const string& b) {
    return a.length() > b.length() || (a.length() == b.length() && a < b);
}
class Solution {
public:
    bool isSubString(const string& s, const string& sub) {
        int i = 0, j = 0, n = s.length(), m = sub.length();
        while(i < n && j < m) {
            if(s[i] == sub[j])
                j++;
            i++;
        }
        return j == m;
    }
    /**
     * @param s: a string
     * @param d: List[str]
     * @return: return a string
     */
    string findLongestWord(string &s, vector<string> &d) {
        // write your code  here
        sort(d.begin(), d.end(), cmp);
        for(auto x: d)
            if(isSubString(s, x))
                return x;
        return "";
    }
};
