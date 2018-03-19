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
 
double diff(int v1, double target)
{
    return abs(v1 - target);
}

class Solution {
public:
    /**
     * @param root: the given BST
     * @param target: the given target
     * @return: the value in the BST that is closest to the target
     */
    void find_closest(TreeNode *root, bool &set, int &ans, double target)
    {
        if(!root)
            return;
        find_closest(root->left, set, ans, target);
        if(!set || diff(root->val, target) < diff(ans, target))
        {
            ans = root->val;
            set = true;
        }
        find_closest(root->right, set, ans, target);
    }
    int closestValue(TreeNode * root, double target) {
        // write your code here
        int ans = 0;
        bool set = false;
        find_closest(root, set, ans, target);
        return ans;
    }
};
