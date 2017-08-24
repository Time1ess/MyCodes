// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-24 11:33
// Last modified: 2017-08-24 11:33
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
    int widthOfBinaryTree(TreeNode* root) {
        if(root == NULL)
            return 0;
        queue<pair<TreeNode*, int>> q;
        int max_width = 1;
        int cnt = 1, left_most = INT_MAX, right_most = 1;
        pair<TreeNode*, int> tmp;
        q.push(make_pair(root, 1));
        while(!q.empty())
        {
            tmp = q.front();
            q.pop();
            right_most = tmp.second;
            left_most = min(left_most, tmp.second);
            if(tmp.first->left)
                q.push(make_pair(tmp.first->left, tmp.second*2));
            if(tmp.first->right)
                q.push(make_pair(tmp.first->right, tmp.second*2+1));
            cnt --;
            if(cnt == 0)
            {
                max_width = max(max_width, right_most - left_most + 1);
                left_most = INT_MAX;
                cnt = q.size();
            }
        }
        return max_width;
    }
};
