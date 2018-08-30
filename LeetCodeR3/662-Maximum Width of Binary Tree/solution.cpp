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
    void find_widths(TreeNode* root, vector<vector<int>>& widths, int p, int height) {
        if (root == nullptr) {
            return;
        }
        if (widths.size() == height) {
            widths.push_back({p, p});
        } else {
            widths[height][0] = min(widths[height][0], p);
            widths[height][1] = max(widths[height][1], p);
        }
        find_widths(root->left, widths, p * 2 - 1, height + 1);
        find_widths(root->right, widths, p * 2, height + 1);
    }
    int widthOfBinaryTree(TreeNode* root) {
        vector<vector<int>> widths;
        find_widths(root, widths, 1, 0);
        int ans = 0;
        for (auto x : widths) {
            ans = max(ans, x[1] - x[0] + 1);
        }
        return ans;
    }
};
