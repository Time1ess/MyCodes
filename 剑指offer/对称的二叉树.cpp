/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    bool isSameTree(TreeNode* t1, TreeNode* t2)
    {
        if(t1 == NULL && t2 == NULL)
            return true;
        if(!t1 || !t2 || t1->val != t2->val)
            return false;
        return isSameTree(t1->left, t2->right) && isSameTree(t1->right, t2->left);
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
    	if(pRoot == NULL)
            return true;
        return isSameTree(pRoot->left, pRoot->right);
    }

};
