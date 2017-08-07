// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-07 09:34
// Last modified: 2017-08-07 09:34
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode *> dnodes;
        int size = nums.size();
        TreeNode *tmp, *node = NULL;
        for(int i = 0; i < size; i++)
        {
            if(dnodes.empty() || dnodes.back()->val > nums[i])
                dnodes.push_back(new TreeNode(nums[i]));
            else
            {
                node = dnodes.back();
                dnodes.pop_back();
                while(!dnodes.empty() && dnodes.back()->val < nums[i])
                {
                    tmp = dnodes.back();
                    dnodes.pop_back();
                    tmp->right = node;
                    node = tmp;
                }
                tmp = new TreeNode(nums[i]);
                tmp->left = node;
                dnodes.push_back(tmp);
            }
        }
        if(!dnodes.empty())
        {
            node = dnodes.back();
            dnodes.pop_back();
            while(!dnodes.empty())
            {
                tmp = dnodes.back();
                dnodes.pop_back();
                tmp->right = node;
                node = tmp;
            }
        }
        return node;
    }
};
