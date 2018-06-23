/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Checker {
public:
    bool checkBST(TreeNode* root, long long& lastVal) {
        if(!root)
            return true;
        if(!checkBST(root->left, lastVal))
            return false;
        if(root->val <= lastVal)
            return false;
        lastVal = root->val;
        return checkBST(root->right, lastVal);
    }
    bool checkBST(TreeNode* root) {
        // write code here
        long long lastVal = (long long)INT_MIN - 1;
        return checkBST(root, lastVal);
    }
};
