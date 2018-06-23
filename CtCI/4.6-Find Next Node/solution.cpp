/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Successor {
public:
    int InOrder(TreeNode* root, int p, int& lastVal) {
        if(!root)
            return -1;
        int ans = InOrder(root->left, p, lastVal);
        if(ans != -1)
            return ans;
        if(lastVal == p)
            return root->val;
        lastVal = root->val;
        return InOrder(root->right, p, lastVal);
    }
    int findSucc(TreeNode* root, int p) {
        // write code here
        int lastVal = -1;
        return InOrder(root, p, lastVal);
    }
};
