// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-15 09:08
// Last modified: 2017-05-15 09:08
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        vector<int> kills;
        int size = pid.size();
        if(size == 0)
            return kills;
        unordered_map<int, vector<int>> m;
        for(int i = 0; i < size; i++)
            m[ppid[i]].push_back(pid[i]);
        queue<int> q;
        q.push(kill);
        while(!q.empty())
        {
            int t = q.front();
            q.pop();
            kills.push_back(t);
            for(auto x: m[t])
                q.push(x);
        }
        return kills;
    }
};
