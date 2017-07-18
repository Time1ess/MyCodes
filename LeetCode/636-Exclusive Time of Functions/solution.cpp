// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-18 09:44
// Last modified: 2017-07-18 09:44
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> s;
        stack<int> child_exec;
        child_exec.push(0);
        int elapsed, ce;
        int id, ts;
        vector<int> ans(n, 0);
        for(auto log: logs)
        {
            int l = -1, r = log.length();
            while(log[++l] != ':');
            while(log[--r] != ':');
            
            id = stoi(log.substr(0, l));
            ts = stoi(log.substr(r+1));
            
            if(log.substr(l+1, r-l-1) == "start")
            {
                s.push(make_pair(id, ts));
                child_exec.push(0);
            }
            else
            {
                pair<int, int> p = s.top();
                ce = child_exec.top();
                s.pop();
                child_exec.pop();
                elapsed = ts - p.second + 1 - ce;
                ans[id] += elapsed;
                
                // Update father's child exec time
                ce = child_exec.top();
                child_exec.pop();
                ce += ts - p.second + 1;
                child_exec.push(ce);
            }
        }
        return ans;
    }
};
