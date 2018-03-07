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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)
            return ans;
        queue<TreeNode *> current_ls;
        current_ls.push(root);
        while(!current_ls.empty())
        {
            vector<int> t;
            queue<TreeNode *> next_ls;
            while(!current_ls.empty())
            {
                TreeNode *front = current_ls.front();
                current_ls.pop();
                t.push_back(front->val);
                if(front->left)
                    next_ls.push(front->left);
                if(front->right)
                    next_ls.push(front->right);
            }
            current_ls = next_ls;
            ans.push_back(t);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
