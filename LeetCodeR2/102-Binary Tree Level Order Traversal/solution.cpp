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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)
            return ans;
        queue<TreeNode*> q1, tmp;
        vector<int> current;
        q1.push(root);
        while(!q1.empty() || !tmp.empty())
        {
            if(q1.empty())
            {
                ans.push_back(current);
                current.clear();
                q1 = tmp;
                while(!tmp.empty())
                    tmp.pop();
                continue;
            }
            TreeNode* node = q1.front();
            q1.pop();
            current.push_back(node->val);
            if(node->left)
                tmp.push(node->left);
            if(node->right)
                tmp.push(node->right);
        }
        if(!current.empty())
            ans.push_back(current);
        return ans;
    }
};
