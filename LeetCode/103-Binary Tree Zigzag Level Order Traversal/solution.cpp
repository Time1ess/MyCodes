// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-29 10:54
// Last modified: 2017-07-29 10:54
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        deque<TreeNode*> qs[2];
        vector<vector<int>> ans;
        if(root == NULL)
            return ans;
        bool left_to_right = true;
        TreeNode *tmp;
        qs[0].push_back(root);
        while(!qs[0].empty() || !qs[1].empty())
        {
            if(left_to_right)
            {
                vector<int> t;
                while(!qs[0].empty())
                {
                    tmp = qs[0].front();
                    qs[0].pop_front();
                    t.push_back(tmp->val);
                    if(tmp->left)
                        qs[1].push_back(tmp->left);
                    if(tmp->right)
                        qs[1].push_back(tmp->right);
                }
                left_to_right = false;
                ans.push_back(t);
            }
            else
            {
                vector<int> t;
                while(!qs[1].empty())
                {
                    tmp = qs[1].back();
                    qs[1].pop_back();
                    t.push_back(tmp->val);
                    if(tmp->right)
                        qs[0].push_front(tmp->right);
                    if(tmp->left)
                        qs[0].push_front(tmp->left);
                }
                left_to_right = true;
                ans.push_back(t);
            }
        }
        return ans;
    }
};
