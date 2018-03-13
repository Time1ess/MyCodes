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
    void dfs(vector<string> &ans, string current, TreeNode *root)
    {
        if(!root)
            return;
        current = current.length() != 0 ? current + "->" + to_string(root->val) : to_string(root->val);
        if(root->left == NULL && root->right == NULL)
        {
            ans.push_back(current);
            return;
        }
        if(root->left)
            dfs(ans, current, root->left);
        if(root->right)
            dfs(ans, current, root->right);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        dfs(ans, "", root);
        return ans;
    }
};
