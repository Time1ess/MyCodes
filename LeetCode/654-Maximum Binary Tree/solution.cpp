// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-07 09:06
// Last modified: 2017-08-07 09:06
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
    TreeNode* constructTree(vector<int>& nums, int left, int right)
    {
        if(left >= right)
            return NULL;
        int max_idx = left;
        for(int i = left; i < right; i++)
            if(nums[i] > nums[max_idx])
                max_idx = i;
        TreeNode* node = new TreeNode(nums[max_idx]);
        node->left = constructTree(nums, left, max_idx);
        node->right = constructTree(nums, max_idx+1, right);
        return node;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return constructTree(nums, 0, nums.size());
    }
};
