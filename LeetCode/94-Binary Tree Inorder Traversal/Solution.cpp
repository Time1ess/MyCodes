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
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode *> tree_s;
        vector<int> ans;
        if(root==NULL)
        return ans;
        TreeNode *current=root,*tmp;
        while(!tree_s.empty()||current)
        {
            if(current)
            {
                tree_s.push(current);
                current=current->left;
            }
            else
            {
                tmp=tree_s.top();
                ans.push_back(tmp->val);
                tree_s.pop();
                current=tmp->right;
            }
        }
        
        return ans; 
    }
};
