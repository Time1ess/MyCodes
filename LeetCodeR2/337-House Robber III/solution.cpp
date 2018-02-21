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
private:
    map<TreeNode*, int> mem;
public:
    int rob(TreeNode* root) {
        if(!root)
            return 0;
        if(mem.find(root) != mem.end())
            return mem[root];
        int left = 0;
        if(root->left)
            left = rob(root->left->left) + rob(root->left->right);
        int right = 0;
        if(root->right)
            right = rob(root->right->left) + rob(root->right->right);
        int ans = max(rob(root->left) + rob(root->right), root->val + left + right);
        mem[root] = ans;
        return ans;
    }
};
