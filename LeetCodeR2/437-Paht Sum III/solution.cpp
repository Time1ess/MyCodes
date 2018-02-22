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
    int pathSum(TreeNode *root, int current, int sum)
    {
        if(!root)
            return 0;
        current += root->val;
        return (current == sum ? 1 : 0) + pathSum(root->left, current, sum) + pathSum(root->right, current, sum);
    }
    int pathSum(TreeNode* root, int sum) {
        if(!root)
            return 0;
        return pathSum(root, 0, sum) + pathSum(root->right, sum) + pathSum(root->left, sum);
    }
};
