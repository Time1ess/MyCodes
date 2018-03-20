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
    /**
     * @param root: a TreeNode
     * @return: a list of integer
     */
    void find_leaves(TreeNode *root, vector<int> &leaves)
    {
        if(!root)
            return;
        find_leaves(root->left, leaves);
        if(root->left == NULL && root->right == NULL)
            leaves.push_back(root->val);
        find_leaves(root->right, leaves);
    }
    
    void find_left_most(TreeNode *root, vector<int> &path)
    {
        if(!root || (root->left == NULL && root->right == NULL))
            return;
        path.push_back(root->val);
        if(root->left)
            find_left_most(root->left, path);
        else if(root->right)
            find_left_most(root->right, path);
    }
    
    void find_right_most(TreeNode *root, vector<int> &path)
    {
        if(!root || (root->left == NULL && root->right == NULL))
            return;
        path.push_back(root->val);
        if(root->right)
            find_right_most(root->right, path);
        else if(root->left)
            find_right_most(root->left, path);
    }
    
    vector<int> boundaryOfBinaryTree(TreeNode * root) {
        // write your code here
        
        if(!root)
            return {};
        else if(root->left == NULL && root->right == NULL)
            return {root->val};
            
        vector<int> ans;
        ans.push_back(root->val);
        TreeNode* node;
        
        // Find left boundary
        node = root->left;
        vector<int> left_boundary;
        find_left_most(node, left_boundary);
        
        // Find all leaves
        vector<int> leaves;
        find_leaves(root, leaves);
        
        // Find right boundary, reverse it
        node = root->right;
        vector<int> right_boundary;
        find_right_most(node, right_boundary);
        reverse(right_boundary.begin(), right_boundary.end());
        for(auto x: left_boundary)
            ans.push_back(x);
        for(auto x: leaves)
            ans.push_back(x);
        for(auto x: right_boundary)
            ans.push_back(x);
        return ans;
    }
};
