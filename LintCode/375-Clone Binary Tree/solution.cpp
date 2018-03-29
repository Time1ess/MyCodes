/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: The root of binary tree
     * @return: root of new tree
     */
    TreeNode * cloneTree(TreeNode * root) {
        // write your code here
        if(!root)
            return NULL;
        TreeNode *new_root = new TreeNode(root->val);
        new_root->left = cloneTree(root->left);
        new_root->right = cloneTree(root->right);
        return new_root;
    }
};
