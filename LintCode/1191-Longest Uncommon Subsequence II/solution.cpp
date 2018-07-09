bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}
class Solution {
public:
    bool check_sub(const string& parent, const string& sub) {
        int i = 0, j = 0;
        int n = parent.length(), m = sub.length();
        while(i < n && j < m) {
            if(parent[i] == sub[j])
                j++;
            i++;
        }
        if(j == m)
            return true;
        return false;
    }
    /**
     * @param strs: List[str]
     * @return: return an integer
     */
    int findLUSlength(vector<string> &strs) {
        // write your code here
        int n = strs.size();
        if(n == 0)
            return 0;
        vector<pair<string, int>> ss;
        for(auto x: strs)
            ss.push_back({x, x.length()});
        sort(ss.begin(), ss.end(), cmp);
        ss.push_back({"", 0});
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n + 1; j++) {
                if(ss[i].second > ss[j].second)
                    return ss[i].second;
                if(i != j && check_sub(ss[j].first, ss[i].first))
                    break;
            }
        }
        return -1;
    }
};
