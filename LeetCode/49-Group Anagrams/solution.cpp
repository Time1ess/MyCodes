// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-26 10:32
// Last modified: 2017-07-26 10:32
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> m;
        string t;
        for(auto str: strs)
        {
            t = str;
            sort(t.begin(), t.end());
            m[t].push_back(str);
        }
        vector<vector<string>> ans;
        for(auto x: m)
            ans.push_back(x.second);
        return ans;
    }
};
