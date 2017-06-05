// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-05 09:08
// Last modified: 2017-06-05 09:08
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        vector<vector<string>> ans, ret;
        unordered_map<string, int> visited;
        for(auto &path: paths)
        {
            int i = path.find(' ');
            string dir = path.substr(0, i);
            while(i != string::npos)
            {
                int lp = path.find('(', i);
                int rp = path.find(')', i);
                string content = path.substr(lp+1, rp-lp-1);
                string fname = dir + "/" + path.substr(i+1, lp-i-1);
                if(visited.find(content) == visited.end())
                {
                    visited[content] = ans.size();
                    vector<string> t;
                    t.emplace_back(fname);
                    ans.emplace_back(t);
                }
                else
                    ans[visited[content]].emplace_back(fname);
                i = path.find(' ', i+1);
            }
        }
        for(auto &vec: ans)
            if(vec.size() > 1)
                ret.emplace_back(vec);
        return ret;
    }
};
