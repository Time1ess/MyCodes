/*
struct UndirectedGraphNode {
    int label;
    vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};*/

#include <unordered_set>

class Path {
public:
    bool check(UndirectedGraphNode* a, UndirectedGraphNode* b) {
        if(!a || !b)
            return false;
        if(a->label == b->label)
            return true;
        unordered_set<int> visited;
        queue<UndirectedGraphNode*> q;
        q.push(a);
        while(!q.empty()) {
            auto node = q.front();
            q.pop();
            if(node->label == b->label)
                return true;
            visited.insert(node->label);
            for(auto next: node->neighbors) {
                if(visited.find(next->label) == visited.end())
                    q.push(next);
            }
        }
        return false;
    }
    bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
        // write code here
        return check(a, b) || check(b, a);
    }
};
