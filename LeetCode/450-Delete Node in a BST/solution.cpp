// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-06 09:23
// Last modified: 2017-05-06 09:23
// Filename: solution.cpp
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
            return root;
        if(!root->left && !root->right)
        {
            if(root->val == key)
                return NULL;
            else
                return root;
        }
        TreeNode *target = root;
        TreeNode *target_parent = NULL;
        while(target)
        {
            if(target->val == key)
                break;
            else if(target->val > key)
            {
                target_parent = target;
                target = target->left;
            }
            else
            {
                target_parent = target;
                target = target->right;
            }
        }
        // No target found
        if(!target)
            return root;
        TreeNode *swap, *swap_parent;
        swap_parent = target;
        if(target->left)
        {
            // Find maximum in target->left
            swap = target->left;
            while(swap->right)
            {
                swap_parent = swap;
                swap = swap->right;
            }
            target->val = swap->val;
            if(swap_parent->left && swap_parent->left->val == swap->val)
                swap_parent->left = swap->left;
            else
                swap_parent->right = swap->left;
        }
        else if(target->right)
        {
            // Find minimum in target->right
            swap = target->right;
            while(swap->left)
            {
                swap_parent = swap;
                swap = swap->left;
            }
            target->val = swap->val;
            if(swap_parent->left && swap_parent->left->val == swap->val)
                swap_parent->left = swap->right;
            else
                swap_parent->right = swap->right;
        }
        else
        {
            // No nodes in target, delete target
            if(target_parent->left && target_parent->left->val == target->val)
                target_parent->left = NULL;
            else
                target_parent->right = NULL;
        }
        return root;
    }
};
