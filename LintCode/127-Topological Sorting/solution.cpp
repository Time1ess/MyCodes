/**
 * Definition for Directed graph.
 * struct DirectedGraphNode {
 *     int label;
 *     vector<DirectedGraphNode *> neighbors;
 *     DirectedGraphNode(int x) : label(x) {};
 * };
 */

class Solution {
public:
    /*
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*>& graph) {
        // write your code here
        int n = graph.size();
        unordered_map<int, int> in_degrees;
        unordered_map<int, DirectedGraphNode*> nodes;
        for(auto x: graph)
            in_degrees[x->label] = 0;
        for(auto x: graph)
        {
            nodes[x->label] = x;
            for(auto y: x->neighbors)
                in_degrees[y->label]++;
        }
        queue<int> free_nodes;
        for(auto x: in_degrees)
            if(x.second == 0)
                free_nodes.push(x.first);
        vector<DirectedGraphNode*> ans;
        while(!free_nodes.empty())
        {
            auto node = free_nodes.front();
            free_nodes.pop();
            ans.push_back(nodes[node]);
            for(auto y: nodes[node]->neighbors)
            {
                in_degrees[y->label]--;
                if(in_degrees[y->label] == 0)
                    free_nodes.push(y->label);
            }
        }
        return ans;
    }
};
