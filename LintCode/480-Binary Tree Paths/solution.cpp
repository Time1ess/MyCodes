/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */


class Solution {
public:
    /*
     * @param root: the root of the binary tree
     * @return: all root-to-leaf paths
     */
    void traverse(TreeNode *root, vector<string> &ans, string current)
    {
        if(!root)
            return;
        current += to_string(root->val);
        if(root->left == NULL && root->right == NULL)
        {
            ans.push_back(current);
            return;
        }
        current += "->";
        if(root->left)
            traverse(root->left, ans, current);
        if(root->right)
            traverse(root->right, ans, current);
    }
    vector<string> binaryTreePaths(TreeNode * root) {
        // write your code here
        vector<string> ans;
        if(!root)
            return ans;
        traverse(root, ans, "");
        return ans;
    }
};
