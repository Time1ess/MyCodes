class Solution {
public:
    /**
     * @param graph: a 2D integers array
     * @return: return a list of integers
     */
    bool safe(vector<vector<int>>& graph,
              unordered_set<int>& visited,
              unordered_set<int>& safe_states, int x) {
        if(safe_states.find(x) != safe_states.end()) {
            return true;
        }
        if(visited.find(x) != visited.end()) {
            return false;
        }
        visited.insert(x);
        int is_safe = true;
        for(auto next: graph[x]) {
            if(is_safe && !safe(graph, visited, safe_states, next)) {
                is_safe = false;
            }
        }
        if(is_safe) {
            safe_states.insert(x);
        }
        return is_safe;
    }
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        // write your code here
        int n = graph.size();
        unordered_set<int> safe_states;
        vector<int> ans;
        for(int i = 0; i < n; i++) {
            unordered_set<int> visited;
            if(safe(graph, visited, safe_states, i)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
