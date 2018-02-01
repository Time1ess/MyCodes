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
     * @param : the root of tree
     * @param : the target sum
     * @return: two number from tree witch sum is n
     */
    void bi_search(TreeNode *root, TreeNode* current, vector<int> &ans, int target)
    {
        if(!current)
            return;
        int size = ans.size();
        if(size == 2)
            return;
        else if(size == 0)
        {
            int diff = target - current->val;
            ans.push_back(current->val);
            bi_search(root, root, ans, diff);
            if(ans.size() == 2)  // Find second elem in tree
                return;
            ans.pop_back();
            bi_search(root, root->left, ans, target);
            bi_search(root, root->right, ans, target);
        }
        else
        {
            if(current->val == target)
            {
                ans.push_back(target);
                return;
            }
            else if(current->val > target)
                bi_search(root, current->left, ans, target);
            else
                bi_search(root, current->right, ans, target);
        }
    }
    vector<int> twoSum(TreeNode * root, int n) {
        // write your code here
        vector<int> ans;
        bi_search(root, root, ans, n);
        return ans;
    }
};
