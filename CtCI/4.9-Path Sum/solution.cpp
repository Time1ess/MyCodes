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
    int pathSumCnt(TreeNode* root, int cur, const int sum) {
        if(!root)
            return 0;
        cur += root->val;
        return (cur == sum ? 1 : 0) + pathSumCnt(root->left, cur, sum) + pathSumCnt(root->right, cur, sum);
    }
    int pathSum(TreeNode* root, int sum) {
        if(!root)
            return 0;
        return pathSumCnt(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};
