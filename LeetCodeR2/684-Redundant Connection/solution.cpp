class Solution {
public:
    int find(unordered_map<int, int> &parents, int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int, int> parents;
        for(auto edge: edges)
        {
            parents[edge[0]] = edge[0];
            parents[edge[1]] = edge[1];
        }
        for(auto edge: edges)
        {
            int p0 = find(parents, edge[0]);
            int p1 = find(parents, edge[1]);
            if(p0 == p1)
                return {edge[0], edge[1]};
            parents[p1] = p0;
        }
        return {-1, -1};
    }
};
