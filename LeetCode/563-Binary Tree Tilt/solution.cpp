// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-23 17:02
// Last modified: 2017-04-23 17:02
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
    int all_sum(TreeNode* root, int &tot_tilt)
    {
        if(root == NULL)
            return 0;
        int lsum = all_sum(root->left, tot_tilt);
        int rsum = all_sum(root->right, tot_tilt);
        tot_tilt += abs(lsum - rsum);
        return root->val + lsum + rsum;
    }
    int findTilt(TreeNode* root) {
        int ans = 0;
        all_sum(root, ans);
        return ans;
    }
};
