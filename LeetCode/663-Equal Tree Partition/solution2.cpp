// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-22 16:00
// Last modified: 2017-08-22 16:00
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
    int sum_nodes(TreeNode* root, set<int> &sums)
    {
        if(root == NULL) return 0;
        int sum = sum_nodes(root->left, sums) + sum_nodes(root->right, sums) + root->val;
        sums.insert(sum);
        return sum;
    }
    bool checkEqualTree(TreeNode* root) {
        if(root == NULL || (!root->left && !root->right))
            return false;
        set<int> sums;
        int all_sum = sum_nodes(root, sums);
        if(all_sum % 2 == 0 && sums.find(all_sum / 2) != sums.end())
            return true;
        else
            return false;
    }
};
