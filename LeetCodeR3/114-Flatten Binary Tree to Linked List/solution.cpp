/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root, TreeNode** last_node) {
        if (root == nullptr) {
            return;
        }
        flatten(root->right, last_node);
        flatten(root->left, last_node);
        root->left = root->right = nullptr;
        if (*last_node != nullptr) {
            root->right = *last_node;
        }
        *last_node = root;
    }
    void flatten(TreeNode* root) {
        TreeNode* last_node = nullptr; 
        flatten(root, &last_node);
    }
};
