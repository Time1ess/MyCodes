// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-04 08:57
// Last modified: 2017-09-04 08:57
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
    int findSecondMinimumValue(TreeNode* root) {
        if(root == NULL || root->left == NULL || root->left->val == root->right->val)
            return -1;
        int minimum = root->val;
        int ans = INT_MAX;
        findSecondMinimumValue(root, minimum, ans);
        return ans;
    }
    void findSecondMinimumValue(TreeNode* root, int &minimum, int &ans)
    {
        if(root == NULL)
            return;
        if(root->val < ans && root->val > minimum)
            ans = root->val;
        findSecondMinimumValue(root->left, minimum, ans);
        findSecondMinimumValue(root->right, minimum, ans);
    }
};
