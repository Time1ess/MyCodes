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
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
    bool isValidBST(TreeNode* root, long long min_val, long long max_val)
    {
        if(!root)
            return true;
        return root->val >= min_val && root->val <= max_val
               && isValidBST(root->left, min_val, root->val - 1)
               && isValidBST(root->right, root->val + 1, max_val);
    }
    bool isValidBST(TreeNode * root) {
        // write your code here
        return isValidBST(root, INT_MIN, INT_MAX);
    }
};
