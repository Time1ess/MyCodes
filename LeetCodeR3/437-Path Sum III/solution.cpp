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
    void pathSum(TreeNode* root, int& ans, int cur, int sum) {
        if(!root) {
            return;
        }
        cur += root->val;
        if(cur == sum) {
            ans++;
        }
        pathSum(root->left, ans, cur, sum);
        pathSum(root->right, ans, cur, sum);
    }
    int pathSum(TreeNode* root, int sum) {
        if(root == nullptr) {
            return 0;
        }
        int ans = 0;
        pathSum(root, ans, 0, sum);
        return ans + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};
