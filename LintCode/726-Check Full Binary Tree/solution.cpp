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
     * @param root: the given tree
     * @return: Whether it is a full tree
     */
    bool isFullTree(TreeNode * root) {
        // write your code here
        if(!root)
            return true;
        if(root->right && root->left)
            return isFullTree(root->right) && isFullTree(root->left);
        else if(root->left == NULL && root->right == NULL)
            return true;
        else
            return false;
    }
};
