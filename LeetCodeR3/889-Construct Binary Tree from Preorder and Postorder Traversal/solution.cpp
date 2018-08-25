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
    TreeNode* constructFromPrePost(vector<int>& pre, int pre_s, int pre_e, vector<int>& post, int post_s, int post_e) {
        if (pre_s >= pre_e) {
            return nullptr;
        } else if (pre_s + 1 == pre_e) {
            return new TreeNode(pre[pre_s]);   
        }
        TreeNode* root = new TreeNode(pre[pre_s]);
        auto idx = find(post.begin(), post.end(), pre[pre_s+1]) - post.begin();
        int cnt = idx - post_s + 1;
        root->left = constructFromPrePost(pre, pre_s + 1, pre_s + 1 + cnt, post, post_s, post_s + cnt);
        root->right = constructFromPrePost(pre, pre_s + 1 + cnt, pre_e, post, post_s + cnt, post_e);
        return root;
    }
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int n = pre.size();
        return constructFromPrePost(pre, 0, n, post, 0, n);
    }
};
