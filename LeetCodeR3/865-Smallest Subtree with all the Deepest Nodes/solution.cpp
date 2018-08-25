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
    TreeNode* subtreeWithAllDeepest(TreeNode* root, int& depth) {
        if (root == nullptr) {
            depth = 0;
            return root;
        }
        int left, right;
        TreeNode* lc = subtreeWithAllDeepest(root->left, left);
        TreeNode* rc = subtreeWithAllDeepest(root->right, right);
        depth = max(left, right) + 1;
        if (left == right) {
            return root;
        } else if (left > right) {
            return lc;
        } else {
            return rc;
        }
    }
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        int depth = 0;
        return subtreeWithAllDeepest(root, depth);
    }
};
