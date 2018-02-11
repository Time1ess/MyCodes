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
    int findTilt(TreeNode* root, int &sum)
    {
        if(!root)
            return 0;
        int left = findTilt(root->left, sum);
        int right = findTilt(root->right, sum);
        sum += abs(left - right);
        return left + right + root->val;
    }
    int findTilt(TreeNode* root) {
        int sum = 0;
        findTilt(root, sum);
        return sum;
    }
};
