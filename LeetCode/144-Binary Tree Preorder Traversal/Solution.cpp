/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 #include <stack>
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> tree_s;
        vector<int> ans;
        if(root==NULL)
        return ans;
        TreeNode *tmp;
        tree_s.push(root);
        while(!tree_s.empty())
        {
            tmp=tree_s.top();
            tree_s.pop();
            ans.push_back(tmp->val);
            if(tmp->right)
            tree_s.push(tmp->right);
            if(tmp->left)
            tree_s.push(tmp->left);
        }
        return ans;
    }
};
