// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-06 09:09
// Last modified: 2017-10-06 09:09
// Filename: solution.cpp
// Description:
class Solution {
public:
    int find_parent(unordered_map<int, int> &m, int t)
    {
        return t == 0 || m[t] == t ? t : find_parent(m, m[t]);
    }
    void merge(unordered_map<int, int> &m, int n1, int n2, int p1, int p2)
    {
        if(p1 == 0)
            m[n1] = p2;
        else if(p2 == 0)
            m[n2] = p1;
        else
            m[p2] = p1;
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int, int> m;
        for(auto edge: edges)
        {
            int n1 = edge[0], n2 = edge[1];
            int p1 = find_parent(m, n1);
            int p2 = find_parent(m, n2);
            if(p1 != 0 && p1 == p2)
                return edge;
            else if(p1 == 0 && p1 == p2)
                m[n1] = m[n2] = min(n1, n2);
            else
                merge(m, n1, n2, p1, p2);
        }
    }
};
