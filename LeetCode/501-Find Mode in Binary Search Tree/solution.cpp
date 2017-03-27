// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 09:39
// Last modified: 2017-03-27 09:39
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
    void inorder(TreeNode* root, int &mct, int &cv, int &ct, vector<int> &ans)
    {
        if(root->left)
            inorder(root->left, mct, cv, ct, ans);
        if(root->val != cv)
        {
            cv = root->val;
            ct = 0;
        }
        ct++;
        if(ct > mct)
        {
            ans.clear();
            mct = ct;
            ans.push_back(cv);
        }
        else if(ct == mct)
            ans.push_back(cv);
        if(root->right)
            inorder(root->right, mct, cv, ct, ans);
    }
    vector<int> findMode(TreeNode* root) {
        vector<int> ans;
        if(root == NULL)
            return ans;
        int most_common_times, current_val, current_times;
        current_val = root->val;
        most_common_times = current_times = 0;
        inorder(root, most_common_times, current_val, current_times, ans);
        return ans;
    }
};
