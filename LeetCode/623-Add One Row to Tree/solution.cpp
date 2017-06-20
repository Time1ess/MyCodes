// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-20 18:12
// Last modified: 2017-06-20 18:12
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
    void insertRow(TreeNode* root, int v, int cur, int d)
    {
        if(root == NULL)
            return;
        if(cur + 1 == d)
        {
            TreeNode *l = new TreeNode(v);
            TreeNode *r = new TreeNode(v);
            l->left = root->left;
            r->right = root->right;
            root->left = l;
            root->right = r;
        }
        else
        {
            insertRow(root->left, v, cur+1, d);
            insertRow(root->right, v, cur+1, d);
        }
    }
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if(root == NULL)
            return root;
        if(d == 1)
        {
            TreeNode *r = new TreeNode(v);
            r->left = root;
            return r;
        }
        else
        {
            insertRow(root, v, 1, d);
            return root;
        }
    }
};
