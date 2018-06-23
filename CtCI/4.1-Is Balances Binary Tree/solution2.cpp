/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Balance {
public:
    int getHeight(TreeNode* root) {
        if(!root)
            return 0;
        
        int left = getHeight(root->left);
        if(left == -1)
            return -1;
        
        int right = getHeight(root->right);
        if(right == -1)
            return -1;
        
        if(abs(left - right) > 1)
            return -1;
        else
            return max(left, right) + 1;
    }
    bool isBalance(TreeNode* root) {
        // write code here
        return getHeight(root) != -1;
    }
};
