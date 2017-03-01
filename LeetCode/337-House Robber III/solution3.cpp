// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 21:01
// Last modified: 2017-03-01 21:01
// Filename: solution3.cpp
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
    int* dp_rob(TreeNode* root)
    {
        int *res = new int[2]{0};
        if(!root)
            return res;
        
        int *left = dp_rob(root->left);
        int *right = dp_rob(root->right);
        res[0] = max(left[0], left[1]) + max(right[0], right[1]);
        res[1] = root->val + left[0] + right[0];
        return res;
    }
    int rob(TreeNode* root) {
        int *res = dp_rob(root);
        return max(res[0], res[1]);
    }
};
