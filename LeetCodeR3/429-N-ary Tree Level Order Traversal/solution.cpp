/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        queue<Node*> current;
        current.push(root);
        vector<vector<int>> levels;
        while (!current.empty()) {
            vector<int> level;
            queue<Node*> next;
            while (!current.empty()) {
                auto front = current.front();
                current.pop();
                level.push_back(front->val);
                for (auto x: front->children) {
                    next.push(x);
                }
            }
            current = next;
            levels.push_back(level);
        }
        return levels;
    }
};
