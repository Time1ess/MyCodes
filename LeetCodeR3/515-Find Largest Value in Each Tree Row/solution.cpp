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
    void find_largest_values(TreeNode* root, vector<int>& ans, int depth) {
        if (root == nullptr) {
            return;
        }
        if (ans.size() == depth) {
            ans.push_back(INT_MIN);
        }
        ans[depth] = max(ans[depth], root->val);
        find_largest_values(root->left, ans, depth + 1);
        find_largest_values(root->right, ans, depth + 1);
    }
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        find_largest_values(root, ans, 0);
        return ans;
    }
};
