// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 11:09
// Last modified: 2017-03-01 11:09
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
    void inorder(TreeNode* root, deque<int>& dq)
    {
        if(root->left)
            inorder(root->left, dq);
        dq.push_back(root->val);
        if(root->right)
            inorder(root->right, dq);
    }
    int getMinimumDifference(TreeNode* root) {
        int t;
        int minimum = 1e9;
        deque<int> dq;
        inorder(root, dq);
        t = dq.front();
        dq.pop_front();
        while(!dq.empty())
        {
            minimum = min(minimum, abs(dq.front()-t));
            t = dq.front();
            dq.pop_front();
        }
        return minimum;
    }
};
