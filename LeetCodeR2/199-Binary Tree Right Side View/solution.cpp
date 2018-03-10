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
    void rightSideView(vector<int> &ans, TreeNode *root, int depth)
    {
        if(!root)
            return;
        if(ans.size() == depth)
            ans.push_back(root->val);
        else
            ans[depth] = root->val;
        rightSideView(ans, root->left, depth+1);
        rightSideView(ans, root->right, depth+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        rightSideView(ans, root, 0);
        return ans;
    }
};
