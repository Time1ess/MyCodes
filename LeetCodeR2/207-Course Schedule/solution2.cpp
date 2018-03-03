class Solution {
public:
    bool dfs_cycle(unordered_map<int, unordered_set<int>> &neighbors, vector<bool> &visited, vector<bool> &on_path, int i)
    {
        if(visited[i])
            return false;
        visited[i] = on_path[i] = true;
        for(auto neighbor: neighbors[i])
            if(on_path[neighbor] || dfs_cycle(neighbors, visited, on_path, neighbor))
                return true;
        on_path[i] = false;
        return false;
    }
    bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, unordered_set<int>> neighbors;
        vector<bool> visited(n, false), on_path(n, false);
        for(auto x: prerequisites)
            neighbors[x.second].insert(x.first);
        for(int i = 0; i < n; i++)
            if(!visited[i] && dfs_cycle(neighbors, visited, on_path, i))
                return false;
        return true;
    }
};
