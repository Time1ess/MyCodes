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
     * @param root: the root of binary tree
     * @param target: An integer
     * @return: all valid paths
     */
    void path_sum_find(vector<vector<int>> &ans, vector<int> &current,
                       TreeNode *root, int target)
    {
        if(!root)
            return;
        current.push_back(root->val);
        int new_target = target - root->val;
        if(root->left == NULL && root->right == NULL && new_target == 0)
            ans.push_back(current);
        else
        {
            path_sum_find(ans, current, root->left, new_target);
            path_sum_find(ans, current, root->right, new_target);
        }
        current.pop_back();
    }
    vector<vector<int>> binaryTreePathSum(TreeNode * root, int target) {
        // write your code here
        vector<vector<int>> ans;
        vector<int> current;
        path_sum_find(ans, current, root, target);
        return ans;
    }
};
