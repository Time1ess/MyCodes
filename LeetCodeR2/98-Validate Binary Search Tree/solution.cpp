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
    bool isValidBST(TreeNode* root, int mmin, int mmax)
    {
        if(!root)
            return true;
        if(root->val < mmin || root->val > mmax)
            return false;
        else if(root->val == INT_MIN && root->left)
            return false;
        else if(root->val == INT_MAX && root->right)
            return false;
        return isValidBST(root->left, mmin, root->val - 1) && isValidBST(root->right, root->val + 1, mmax);
    }
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, INT_MIN, INT_MAX);
    }
};
