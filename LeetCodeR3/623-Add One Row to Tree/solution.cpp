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
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (root == nullptr) {
            return nullptr;
        } else if (d == 1) {
            TreeNode* new_root = new TreeNode(v);
            new_root->left = root;
            return new_root;
        } else if (d == 2) {
            TreeNode* l = new TreeNode(v);
            l->left = root->left;
            root->left = l;
            TreeNode* r = new TreeNode(v);
            r->right = root->right;
            root->right = r;
            return root;
        }
        root->left = addOneRow(root->left, v, d - 1);
        root->right = addOneRow(root->right, v, d - 1);
        return root;
    }
};
