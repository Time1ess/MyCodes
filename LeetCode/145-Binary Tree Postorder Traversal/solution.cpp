// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-25 09:42
// Last modified: 2017-03-25 09:42
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root)
            return ans;
        stack<TreeNode*> s;
        TreeNode* t;
        s.push(root);
        while(!s.empty())
        {
            t = s.top();
            s.pop();
            ans.push_back(t->val);
            if(t->left)
                s.push(t->left);
            if(t->right)
                s.push(t->right);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
