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
    /*
     * @param root: The root of the binary search tree.
     * @param value: Remove the node with given value.
     * @return: The root of the binary search tree after removal.
     */
    TreeNode* delete_max_in_subtree(TreeNode* root)
    {
        if(!root)
            return NULL;
        if(root->right)
        {
            root->right = delete_max_in_subtree(root->right);
            return root;
        }
        else
        {
            TreeNode* new_root = root->left;
            delete root;
            return new_root;
        }
    }
    TreeNode* delete_min_in_subtree(TreeNode* root)
    {
        if(!root)
            return NULL;
        if(root->left)
        {
            root->left = delete_min_in_subtree(root->left);
            return root;
        }
        else
        {
            TreeNode* new_root = root->right;
            delete root;
            return new_root;
        }
    }
    int max_in_subtree(TreeNode* root)
    {
        if(!root)
            return INT_MIN;
        if(root->right)
            return max_in_subtree(root->right);
        return root->val;
    }
    int min_in_subtree(TreeNode* root)
    {
        if(!root)
            return INT_MAX;
        if(root->left)
            return min_in_subtree(root->left);
        return root->val;
    }
    TreeNode * removeNode(TreeNode * root, int value) {
        // write your code here
        if(!root)
            return NULL;
        if(root->val == value)
        {
            if(root->left)
            {
                root->val = max_in_subtree(root->left);
                root->left = delete_max_in_subtree(root->left);
            }
            else if(root->right)
            {
                root->val = min_in_subtree(root->right);
                root->right = delete_min_in_subtree(root->right);
            }
            else
            {
                delete root;
                return NULL;
            }
        }
        else if(root->val < value)
            root->right = removeNode(root->right, value);
        else
            root->left = removeNode(root->left, value);
        return root;
    }
};
