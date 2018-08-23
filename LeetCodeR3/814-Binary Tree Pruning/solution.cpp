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
    bool pruneTreeNoOne(TreeNode* root) {
        if (root == nullptr) {
            return false;
        }
        bool left = pruneTreeNoOne(root->left);
        bool right = pruneTreeNoOne(root->right);
        if (left == false) {
            delete root->left;
            root->left = nullptr;
        }
        if (right == false) {
            delete root->right;
            root->right = nullptr;
        }
        return root->val == 1 || left || right;
    }
    TreeNode* pruneTree(TreeNode* root) {
        if (!pruneTreeNoOne(root)) {
            delete root;
            return nullptr;
        }
        return root;
    }
};
