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
    vector<int> postorder(Node* root) {
        if (root == nullptr) {
            return {};
        }
        stack<Node*> s;
        vector<int> ans;
        Node* last = nullptr;
        s.push(root);
        while (!s.empty()) {
            Node* top = s.top();
            int n = top->children.size();
            if (n == 0 || top->children[n-1] == last) {
                s.pop();
                ans.push_back(top->val);
                last = top;
                continue;
            }
            for (int i = n - 1; i >= 0; i--) {
                s.push(top->children[i]);
            }
        }
        return ans;
    }
};
