/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    TreeLinkNode* find_next_child(TreeLinkNode* node) {
        while (node) {
            if (node->left != nullptr) {
                return node->left;
            } else if(node->right != nullptr) {
                return node->right;
            }
            node = node->next;
        }
        return nullptr;
    }
    void connect(TreeLinkNode *root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return;
        }
        if (root->left) {
            root->left->next = root->right != nullptr ? root->right : find_next_child(root->next);
        }
        if (root->right) {
            root->right->next = find_next_child(root->next);
        }
        connect(root->right);
        connect(root->left);
    }
};
