/*
struct UndirectedGraphNode {
    int label;
    vector<struct UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {}
};*/

#include <unordered_set>

class Path {
public:
    bool HasPath(unordered_set<int>& visited, UndirectedGraphNode* start, UndirectedGraphNode* dest){
        if(start->label == dest->label)
            return true;
        visited.insert(start->label);
        for(auto next: start->neighbors) {
            if(visited.find(next->label) == visited.end() && HasPath(visited, next, dest))
                return true;
        }
        return false;
    }
    bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
        if(!a || !b)
            return false;
        unordered_set<int> visited;
        if(HasPath(visited, a, b))
            return true;
        visited.clear();
        return HasPath(visited, b, a);
    }
};
