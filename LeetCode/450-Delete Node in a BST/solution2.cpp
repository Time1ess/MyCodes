// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-06 09:32
// Last modified: 2017-05-06 09:32
// Filename: solution2.cpp
// Description:
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return NULL;
        if(key < root->val)
            root->left = deleteNode(root->left, key);
        else if(key > root->val)
            root->right = deleteNode(root->right, key);
        else
        {
            if(root->left)
            {
                TreeNode* maximum = root->left;
                while(maximum->right)
                    maximum = maximum->right;
                root->val = maximum->val;
                root->left = deleteNode(root->left, maximum->val);
            }
            else
            {
                TreeNode* right = root->right;
                delete root;
                return right;
            }
        }
        return root;
    }
};
