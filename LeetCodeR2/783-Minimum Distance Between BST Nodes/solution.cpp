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
    void in_order(TreeNode* root, TreeNode **prev, int &ans)
    {
        if(!root)
            return;
        in_order(root->left, prev, ans);
        if(*prev != NULL)
            ans = min(ans, abs(root->val - (*prev)->val));
        *prev = root;
        in_order(root->right, prev, ans);
    }

    int minDiffInBST(TreeNode* root) {
        int ans = INT_MAX;
        TreeNode *prev = NULL;
        in_order(root, &prev, ans);
        return ans; 
    }
};
