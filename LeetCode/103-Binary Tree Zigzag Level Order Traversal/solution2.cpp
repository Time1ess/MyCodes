// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-29 11:01
// Last modified: 2017-07-29 11:01
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL)
            return ans;
        queue<TreeNode *> q;
        bool left_to_right = true;
        TreeNode *t;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> tmp(size, 0);
            for(int i = 0; i < size; i++)
            {
                t = q.front();
                q.pop();
                tmp[left_to_right? i : size - i - 1] = t->val;
                if(t->left)
                    q.push(t->left);
                if(t->right)
                    q.push(t->right);
            }
            ans.push_back(tmp);
            left_to_right = !left_to_right;
        }
        return ans;
    }
};
