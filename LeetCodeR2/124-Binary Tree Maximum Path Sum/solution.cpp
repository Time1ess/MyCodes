/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
typedef long long ll;

class Solution {
public:
    ll maxPathSum(TreeNode* root, ll &maximum_path)
    {
        if(!root)
            return INT_MIN;
        ll left = INT_MIN, right = INT_MIN;
        ll lans = maxPathSum(root->left, left);
        ll rans = maxPathSum(root->right, right);
        maximum_path = max((ll)root->val, max(left, right) + root->val);
        return max(max(lans, rans), root->val + (left > 0 ? left : 0) + (right > 0 ? right : 0));
    }
    int maxPathSum(TreeNode* root) {
        if(!root)
            return 0;
        ll max_path = INT_MIN;
        return maxPathSum(root, max_path);
    }
};
