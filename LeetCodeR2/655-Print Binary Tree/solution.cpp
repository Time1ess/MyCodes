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
    int get_depth(TreeNode* root)
    {
        if(!root)
            return 0;
        return 1 + max(get_depth(root->left), get_depth(root->right));
    }
    void fill_vector(TreeNode *root, vector<vector<string>> &ans, int d, int l, int r)
    {
        if(!root)
            return;
        int m = l + (r - l) / 2;
        ans[d][m] = to_string(root->val);
        fill_vector(root->left, ans, d+1, l, m);
        fill_vector(root->right, ans, d+1, m + 1, r);
    }
    vector<vector<string>> printTree(TreeNode* root) {
        if(!root)
            return {};
        int depth = get_depth(root);
        int l = 0, r = pow(2, depth) - 1;
        vector<vector<string>> ans(depth, vector<string>(r, ""));
        fill_vector(root, ans, 0, l, r);
        return ans;
    }
};
