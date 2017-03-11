// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-11 15:43
// Last modified: 2017-03-11 15:43
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
    TreeNode* construct(vector<int>& nums, int s, int e)
    {
        if(s >= e)
            return NULL;
        int mid = (s + e) >> 1;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = construct(nums, s, mid);
        root->right = construct(nums, mid+1, e);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return construct(nums, 0, nums.size());
    }
};
