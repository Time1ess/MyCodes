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
    void connect(TreeLinkNode *root) {
        if (root == nullptr || root->left == nullptr || root->right == nullptr) {
            return;
        }
        root->left->next = root->right;
        root->right->next = root->next != nullptr ? root->next->left : nullptr;
        connect(root->left);
        connect(root->right);
    }
};
