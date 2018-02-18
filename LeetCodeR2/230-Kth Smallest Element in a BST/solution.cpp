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
    void kthSmallest(TreeNode* root, int &count, int &ans)
    {
        if(!root || !count)
            return;
        kthSmallest(root->left, count, ans);
        count--;
        if(count == 0)
            ans = root->val;
        kthSmallest(root->right, count, ans);
    }
    int kthSmallest(TreeNode* root, int k) {
        int count = k;
        int ans = 0;
        kthSmallest(root, count, ans);
        return ans;
    }
};
