/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool SameTree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot2)
            return true;
        else if(!pRoot1)
            return false;
        else
            return pRoot1->val == pRoot2->val && SameTree(pRoot1->left, pRoot2->left)
            	&& SameTree(pRoot1->right, pRoot2->right);
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot1 || !pRoot2)
            return false;
        return SameTree(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2)
            || HasSubtree(pRoot1->right, pRoot2);
    }
};
