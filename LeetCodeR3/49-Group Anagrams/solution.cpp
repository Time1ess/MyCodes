class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anas;
        for(auto s: strs) {
            string sorted_s = s;
            sort(sorted_s.begin(), sorted_s.end());
            anas[sorted_s].push_back(s);
        }
        vector<vector<string>> ans;
        for(auto p: anas) {
            ans.push_back(p.second);
        }
        return ans;
    }
};
