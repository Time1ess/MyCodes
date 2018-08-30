class Solution {
public:
    int find_parent(unordered_map<int, int>& parents, int x) {
        if (x != parents[x]) {
            parents[x] = find_parent(parents, parents[x]);
        }
        return parents[x];
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        unordered_map<int, int> parents;
        for (auto edge : edges) {
            parents[edge[0]] = edge[0];
            parents[edge[1]] = edge[1];
        }
        vector<int> ans;
        for (auto edge : edges) {
            int x = edge[0];
            int y = edge[1];
            int px = find_parent(parents, x);
            int py = find_parent(parents, y);
            if (px == py) {
                ans = {x, y};
                continue;
            }
            parents[px] = py;
        }
        return ans;
    }
};
