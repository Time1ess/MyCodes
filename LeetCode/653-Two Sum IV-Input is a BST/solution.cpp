// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-08 09:15
// Last modified: 2017-08-08 09:15
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
    bool findTarget(TreeNode* root, int k) {
        if(root == NULL)
            return false;
        queue<TreeNode*> q;
        set<int> s;
        q.push(root);
        while(!q.empty())
        {
            root = q.front();
            q.pop();
            if(s.find(k-root->val) != s.end())
                return true;
            s.insert(root->val);
            if(root->left)
                q.push(root->left);
            if(root->right)
                q.push(root->right);
        }
        return false;
    }
};
