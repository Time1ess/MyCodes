/**
 * Definition for Undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    /**
     * @param graph: a list of Undirected graph node
     * @param A: nodeA
     * @param B: nodeB
     * @return:  the length of the shortest path
     */
    int shortestPath(vector<UndirectedGraphNode*> graph, UndirectedGraphNode* A, UndirectedGraphNode* B) {
        // Write your code here
        unordered_map<int, vector<int>> g;
        for(auto x: graph)
            for(auto y: x->neighbors)
                g[x->label].push_back(y->label);
        unordered_set<int> visited;
        queue<pair<int, int>> trace;
        trace.push({A->label, 0});
        visited.insert(A->label);
        while(!trace.empty())
        {
            auto front = trace.front();
            trace.pop();
            if(front.first == B->label)
                return front.second;
            for(auto neighbor: g[front.first])
            {
                if(visited.find(neighbor) != visited.end())
                    continue;
                visited.insert(neighbor);
                trace.push({neighbor, front.second + 1});
            }
        }
        return -1;
    }
};
