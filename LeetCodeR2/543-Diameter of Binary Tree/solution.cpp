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
    int max_diameter_with_length(TreeNode* root, int &ans)
    {
        if(!root)
            return 0;
        int left = max_diameter_with_length(root->left, ans);
        int right = max_diameter_with_length(root->right, ans);
        ans = max(ans, left + right);
        return 1 + max(left, right);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root)
            return 0;
        int ans = 0;
        max_diameter_with_length(root, ans);
        return ans;
    }
};
