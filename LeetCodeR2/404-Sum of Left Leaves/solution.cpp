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
    void traverse_sum(TreeNode* root, int &sum, bool left)
    {
        if(!root)
            return;
        if(root->left == NULL && root->right == NULL)
        {
            if(left)
                sum += root->val;
            return;
        }
        traverse_sum(root->left, sum, true);
        traverse_sum(root->right, sum, false);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        if(!root)
            return 0;
        if(root->left == NULL && root->right == NULL)
            return sum;
        traverse_sum(root, sum, true);
        return sum;
    }
};
