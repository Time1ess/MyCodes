// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 11:14
// Last modified: 2017-04-07 11:14
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
    bool isSymmetric(TreeNode* root) {
        if(root == NULL)
            return true;
        queue<TreeNode *> p, q;
        TreeNode *t1, *t2;
        p.push(root->left);
        q.push(root->right);
        while(!p.empty() && !q.empty())
        {
            t1 = p.front();p.pop();
            t2 = q.front();q.pop();
            if(t1 == NULL && t2 == NULL)
                continue;
            else if((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL))
                return false;
            else if(t1->val != t2->val)
                return false;
            p.push(t1->left);
            p.push(t1->right);
            q.push(t2->right);
            q.push(t2->left);
        }
        return true;
    }
};
