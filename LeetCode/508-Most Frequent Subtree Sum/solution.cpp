// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-13 10:20
// Last modified: 2017-02-13 10:20
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
    int subtree_sum(TreeNode* root, map<int,int> &ts)
    {
        if(root == NULL)
            return 0;
        int s = root->val+subtree_sum(root->left, ts)+subtree_sum(root->right, ts);
        ts[s]++;
        return s;
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<pair<int, int>> _result;
        vector<int> result;
        if(root == NULL)
            return result;
        map<int, int> ts;
        subtree_sum(root, ts);
        for(auto it_pair:ts)
        {
            if(_result.empty())
                _result.push_back(it_pair);
            else
            {
                pair<int, int> old = _result[0];
                int old_cnt, old_idx;
                old_idx = old.first;
                old_cnt = old.second;
                if(it_pair.second > old_cnt)
                {
                    _result.clear();
                    _result.push_back(it_pair);
                }
                else if(it_pair.second == old_cnt)
                {
                    _result.push_back(it_pair);
                }
            }
        }
        for(auto it_pair:_result)
            result.push_back(it_pair.first);
        return result;
    }

};
