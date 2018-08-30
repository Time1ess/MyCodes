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
    TreeNode* duplicate(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* new_root = new TreeNode(0);
        new_root->left = duplicate(root->left);
        new_root->right = duplicate(root->right);
        return new_root;
    }
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<vector<TreeNode*>> ans{{}, {new TreeNode(0)}};
        for (int x = 2; x <= N; x++) {
            vector<TreeNode*> cur;
            for (int left = 0; left < x; left++) {
                int right = x - left - 1;
                for (auto l : ans[left]) {
                    for (auto r : ans[right]) {
                        TreeNode* root = new TreeNode(0);
                        root->left = duplicate(l);
                        root->right = duplicate(r);
                        cur.push_back(root);
                    }
                }
            }
            ans.push_back(cur);
        }
        return ans[N];
    }
};
