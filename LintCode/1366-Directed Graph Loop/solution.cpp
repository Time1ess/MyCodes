class Solution {
public:
    /**
     * @param start: The start points set
     * @param end: The end points set
     * @return: Return if the graph is cyclic
     */
    bool dfs(unordered_map<int, vector<int>>& adjs, unordered_set<int>& visited,
             int x) {
        if(visited.find(x) != visited.end())
            return true;
        visited.insert(x);
        for(auto y: adjs[x]) {
            if(dfs(adjs, visited, y))
                return true;
        }
        visited.erase(x);
        return false;
    }
    bool isCyclicGraph(vector<int> &start, vector<int> &end) {
        // Write your code here
        unordered_map<int, vector<int>> adjs;
        int n = start.size();
        for(int i = 0; i < n; i++) {
            if(start[i] == end[i])
                return true;
            adjs[start[i]].push_back(end[i]);
        }
        for(auto x: start) {
            unordered_set<int> visited;
            if(dfs(adjs, visited, x))
                return true;
        }
        return false;
    }
};
