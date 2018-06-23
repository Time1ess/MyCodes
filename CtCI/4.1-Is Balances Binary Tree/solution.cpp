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
    bool isBalance(TreeNode* root, int& depth) {
        if(!root) {
            depth = 0;
            return true;
        }
        int left = 0, right = 0;
        bool balance = isBalance(root->left, left) && isBalance(root->right, right);
        depth = max(left, right) + 1;
        return balance && abs(left - right) <= 1;
    }
    bool isBalance(TreeNode* root) {
        // write code here
        int depth = 0;
        return isBalance(root, depth);
    }
};
