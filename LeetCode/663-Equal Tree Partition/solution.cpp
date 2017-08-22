// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-22 15:55
// Last modified: 2017-08-22 15:55
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
    int sum_nodes(TreeNode* root, map<TreeNode*, int> &sums)
    {
        if(root == NULL) return 0;
        sums[root] = sum_nodes(root->left, sums) + sum_nodes(root->right, sums) + root->val;
        return sums[root];
    }
    bool checkEqualTree(TreeNode* root) {
        if(root == NULL || (!root->left && !root->right))
            return false;
        map<TreeNode*, int> sums;
        queue<TreeNode*> q;
        int all_sum = sum_nodes(root, sums);
        q.push(root);
        while(!q.empty())
        {
            TreeNode *tmp = q.front();
            q.pop();
            if(sums[tmp] * 2 == all_sum)
                return true;
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->right);
        }
        return false;
    }
};
