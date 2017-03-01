// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 21:09
// Last modified: 2017-03-01 21:09
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
    int map_rob(TreeNode* root, map<TreeNode *, int>& m)
    {
        if(!root)
            return 0;
        if(m.find(root)!=m.end())
            return m[root];
        int val = 0;
        if(root->left)
            val += map_rob(root->left->left, m) + map_rob(root->left->right, m);
        if(root->right)
            val += map_rob(root->right->left, m) + map_rob(root->right->right, m);
        val = max(root->val + val, map_rob(root->left, m) + map_rob(root->right, m));
        m[root] = val;
        return val;
    }
    int rob(TreeNode* root) {
        map<TreeNode *, int> m;
        return map_rob(root, m);
    }
};
