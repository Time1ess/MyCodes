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
    void ConvertNode(TreeNode* root, TreeNode **last_node)
    {
        if(!root)
            return;
        ConvertNode(root->left, last_node);
        if(*last_node)
            (*last_node)->right = root;
        root->left = *last_node;
        *last_node = root;
        ConvertNode(root->right, last_node);
    }
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode *last_node = NULL;
        ConvertNode(pRootOfTree, &last_node);
        while(last_node && last_node->left)
            last_node = last_node->left;
        return last_node;
    }
};
