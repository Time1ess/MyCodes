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
    int get_min(TreeNode* root)
    {
        return root->left ? get_min(root->left) : root->val;
    }
    int get_max(TreeNode* root)
    {
        return root->right ? get_max(root->right) : root->val;
    }
    void get_minimum_diff(TreeNode* root, int &ans)
    {
        if(!root)
            return;
        int max_left = root->left ? get_max(root->left) : INT_MIN;
        int min_right = root->right ? get_min(root->right) : INT_MIN;
        if(root->left && root->right)
            ans = min(ans, min(abs(root->val - max_left), abs(root->val - min_right)));
        else if(root->right)
            ans = min(ans, abs(root->val - min_right));
        else if(root->left)
            ans = min(ans, abs(root->val - max_left));
        get_minimum_diff(root->left, ans);
        get_minimum_diff(root->right, ans);
    }
    int getMinimumDifference(TreeNode* root) {
        int ans = INT_MAX;
        get_minimum_diff(root, ans);
        return ans;
    }
};
