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
     * @param root: given BST
     * @param minimum: the lower limit
     * @param maximum: the upper limit
     * @return: the root of the new tree 
     */
    void deleteTree(TreeNode *root)
    {
        if(!root)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    TreeNode * trimBST(TreeNode * root, int minimum, int maximum) {
        // write your code here
        if(!root)
            return NULL;
        if(root->val < minimum)
        {
            TreeNode *right = trimBST(root->right, minimum, maximum);
            root->right = NULL;
            deleteTree(root);
            return right;
        }
        else if (root->val >= minimum && root->val <= maximum)
        {
            root->left = trimBST(root->left, minimum, maximum);
            root->right = trimBST(root->right, minimum, maximum);
            return root;
        }
        else
        {
            TreeNode *left = trimBST(root->left, minimum, maximum);
            root->left = NULL;
            deleteTree(root);
            return left;
        }
    }
};
