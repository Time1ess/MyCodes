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
     * @return: True if this Binary tree is Balanced, or false.
     */
    bool isBalanced(TreeNode *root, int &depth)
    {
        if(!root)
        {
            depth = 0;
            return true;
        }
        int left;
        int right;
        bool balanced = isBalanced(root->left, left) && isBalanced(root->right, right);
        depth = max(left, right) + 1;
        return balanced && abs(left - right) <= 1;
    }
    bool isBalanced(TreeNode * root) {
        // write your code here
        int depth;
        return isBalanced(root, depth);
    }
};
