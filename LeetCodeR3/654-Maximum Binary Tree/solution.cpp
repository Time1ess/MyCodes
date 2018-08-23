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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums, int l, int r) {
        if (l == r) {
            return nullptr;
        } else if (l + 1 == r) {
            return new TreeNode(nums[l]);
        }
        int idx = l;
        for (int i = l + 1; i < r; i++) {
            if (nums[idx] < nums[i]) {
                idx = i;
            }
        }
        TreeNode* root = new TreeNode(nums[idx]);
        root->left = constructMaximumBinaryTree(nums, l, idx);
        root->right = constructMaximumBinaryTree(nums, idx + 1, r);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        return constructMaximumBinaryTree(nums, 0, n);
    }
};
