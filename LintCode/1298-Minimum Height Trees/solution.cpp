class Solution {
public:
    void dfs(unordered_map<int, vector<int>>& adjs, vector<bool>& visited,
            int cur, int depth, int& curDepth, int globalMinDepth) {
        if(visited[cur] || curDepth > globalMinDepth)
            return;
        depth++;
        curDepth = max(curDepth, depth);
        visited[cur] = true;
        for(auto y: adjs[cur]) {
            dfs(adjs, visited, y, depth, curDepth, globalMinDepth);
        }
        visited[cur] = false;
    }
    
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<bool> visited(n, false);
        unordered_map<int, vector<int>> adjs;
        for(auto x: edges) {
            adjs[x.first].push_back(x.second);
            adjs[x.second].push_back(x.first);
        }
        vector<int> ans;
        int minHeight = INT_MAX;
        for(int i = 0; i < n; i++) {
            int depth = 0;
            dfs(adjs, visited, i, 0, depth, minHeight);
            if (depth < minHeight) {
                minHeight = depth;
                ans.clear();
                ans.push_back(i);
            } else if(depth == minHeight) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
