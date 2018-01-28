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
    void InOrderTraverse(TreeNode* root, TreeNode** prev, TreeNode **first, TreeNode **second)
    {
        if(!root)
            return;
        InOrderTraverse(root->left, prev, first, second);
        if(*first == NULL && (*prev)->val >= root->val)
            *first = *prev;
        if(*first != NULL && (*prev)->val >= root->val)
            *second = root;
        *prev = root;
        InOrderTraverse(root->right, prev, first, second);
    }
    void recoverTree(TreeNode* root) {
        TreeNode *first, *second, *prev;
        TreeNode *tmp = new TreeNode(INT_MIN);
        prev = tmp;
        first = second = NULL;
        InOrderTraverse(root, &prev, &first, &second);
        delete tmp;
        tmp = NULL;
        if(first && second)
            swap(first->val, second->val);
    }
};
