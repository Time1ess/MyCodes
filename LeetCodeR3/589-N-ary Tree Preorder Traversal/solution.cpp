/*
// Definition for a Node.
class Node {
public:
    int val;
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
    vector<int> preorder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        stack<Node*> s;
        vector<int> ans;
        s.push(root);
        while (!s.empty()) {
            auto top = s.top();
            s.pop();
            ans.push_back(top->val);
            int n = top->children.size();
            for (int i = n - 1; i >= 0; i--) {
                s.push(top->children[i]);
            }
        }
        return ans;
    }
};
