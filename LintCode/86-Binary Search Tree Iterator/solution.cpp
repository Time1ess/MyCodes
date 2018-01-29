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
 * Example of iterate a tree:
 * BSTIterator iterator = BSTIterator(root);
 * while (iterator.hasNext()) {
 *    TreeNode * node = iterator.next();
 *    do something for node
 */


class BSTIterator {
private:
    stack<TreeNode *> s;
public:
    /*
    * @param root: The root of binary tree.
    */BSTIterator(TreeNode * root) {
        // do intialization if necessary
        while(root)
        {
            s.push(root);
            root = root->left;
        }
    }

    /*
     * @return: True if there has next node, or false
     */
    bool hasNext() {
        return !s.empty();
        // write your code here
    }

    /*
     * @return: return next node
     */
    TreeNode * next() {
        // write your code here
        TreeNode* top = s.top();
        s.pop();
        TreeNode* tmp = top->right;
        while(tmp)
        {
            s.push(tmp);
            tmp = tmp->left;
        }
        return top;
    }
};
