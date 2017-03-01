// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 10:08
// Last modified: 2017-03-01 10:08
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
    int get_min_or_max(TreeNode* root, bool getmin)
    {
        if(getmin)
            return root->left? get_min_or_max(root->left, getmin): root->val;
        else
            return root->right? get_min_or_max(root->right, getmin): root->val;
    }
    int getMinimumDifference(TreeNode* root) {
        int minimum = 1e9;
        if(root->left)
        {
            minimum = min(minimum, abs(root->val-get_min_or_max(root->left, false)));
            minimum = min(minimum, getMinimumDifference(root->left));
        }
        if(root->right)
        {
            minimum = min(minimum, abs(root->val-get_min_or_max(root->right, true)));
            minimum = min(minimum, getMinimumDifference(root->right));
        }
        return minimum;
    }
};
