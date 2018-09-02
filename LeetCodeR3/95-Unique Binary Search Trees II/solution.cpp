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
    vector<TreeNode*> generateTrees(int l, int r) {
        if (l > r) {
            return {nullptr};
        } else if (l == r) {
            return {new TreeNode(l)};
        }
        vector<TreeNode*> ans;
        for (int x = l; x <= r; x++) {
            auto left = generateTrees(l, x - 1);
            auto right = generateTrees(x + 1, r);
            for (auto lc : left) {
                for (auto rc : right) {
                    TreeNode* root = new TreeNode(x);
                    root->left = lc;
                    root->right = rc;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) {
            return {};
        }
        return generateTrees(1, n);
    }
};
