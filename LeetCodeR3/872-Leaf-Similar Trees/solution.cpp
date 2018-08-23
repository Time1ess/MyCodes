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
    void find_leaf_vals(TreeNode* root, vector<int>& vals) {
        if (root == nullptr) {
            return;
        } else if (root->left == nullptr && root->right == nullptr) {
            vals.push_back(root->val);
            return;
        }
        find_leaf_vals(root->left, vals);
        find_leaf_vals(root->right, vals);
    }
    bool vals_equal(vector<int>& vals1, vector<int>& vals2) {
        if (vals1.size() != vals2.size()) {
            return false;
        }
        int n = vals1.size();
        for (int i = 0; i < n; i++) {
            if (vals1[i] != vals2[i]) {
                return false;
            }
        }
        return true;
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> vals1, vals2;
        find_leaf_vals(root1, vals1);
        find_leaf_vals(root2, vals2);
        return vals_equal(vals1, vals2);
    }
};
