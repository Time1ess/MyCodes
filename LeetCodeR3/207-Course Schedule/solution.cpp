class Solution {
public:
    bool dfs_circle(unordered_map<int, unordered_set<int>>& edges, vector<bool>& visited, vector<bool>& on_path, int i) {
        if (visited[i]) {
            return false;
        }
        visited[i] = on_path[i] = true;
        for (auto next: edges[i]) {
            if (on_path[next] || dfs_circle(edges, visited, on_path, next)) {
                return true;
            }
        }
        on_path[i] = false;
        return false;
    }
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, unordered_set<int>> edges;
        for (auto p: prerequisites) {
            edges[p.second].insert(p.first);
        }
        vector<bool> visited(numCourses, false), on_path(numCourses, false);
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i] && dfs_circle(edges, visited, on_path, i)) {
                return false;
            }
        }
        return true;
    }
};
