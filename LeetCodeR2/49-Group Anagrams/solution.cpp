class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for(auto str: strs)
        {
            string sorted_str = str;
            sort(sorted_str.begin(), sorted_str.end());
            groups[sorted_str].push_back(str);
        }
        vector<vector<string>> ans;
        for(auto it: groups)
            ans.push_back(it.second);
        return ans;
    }
};
