// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-03 09:13
// Last modified: 2017-08-03 09:13
// Filename: solution.cpp
// Description:
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(root == NULL || (root->left == NULL && root->right == NULL))
            return;
        if(root->left && root->right)
        {
            root->left->next = root->right;
            if(root->next)
            {
                TreeLinkNode *node = root->next;
                while(node->next && (node->left == NULL && node->right == NULL))
                    node = node->next;
                root->right->next = node->left ? node->left: node->right;
            }
        }
        else if(root->next)
        {
            TreeLinkNode *node = root->next;
            while(node->next && (node->left == NULL && node->right == NULL))
                node = node->next;
            if(root->left)
                root->left->next = node->left ? node->left: node->right;
            else
                root->right->next = node->left ? node->left: node->right;
        }
        connect(root->right);
        connect(root->left);
    }
};
