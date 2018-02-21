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
    int rob(TreeNode* root) {
        vector<int> ans = subrob(root);
        return max(ans[0], ans[1]);
    }
    vector<int> subrob(TreeNode *root)
    {
        if(!root)
            return {0, 0};
        vector<int> left = subrob(root->left);
        vector<int> right = subrob(root->right);
        vector<int> ans(2, 0);
        
        ans[0] = root->val + left[1] + right[1];  // include root
        ans[1] = max(left[0], left[1]) + max(right[0], right[1]);  // exclude root
        return ans;
    }
};
