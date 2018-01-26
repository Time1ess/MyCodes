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
    TreeNode* kThNodeCore(TreeNode* pRoot, int &k)
    {
        if(!pRoot)
            return NULL;
        TreeNode* target = kThNodeCore(pRoot->left, k);
        if(!target)
        {
            if(k == 1)
                return pRoot;
            k--;
            target = kThNodeCore(pRoot->right, k);
        }
        return target;
        
    }
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        int kk = k;
        return kThNodeCore(pRoot, kk);
    }
};
