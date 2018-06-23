/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class TreeLevel {
public:
    void getLevelNodes(TreeNode* root, ListNode** tail, int cur, int tar) {
        if(!root)
            return;
        if(cur == tar) {
            ListNode* newTail = new ListNode(root->val);
            (*tail)->next = newTail;
            (*tail) = newTail;
            return;  // No need to deep down.
        }
        getLevelNodes(root->left, tail, cur + 1, tar);
        getLevelNodes(root->right, tail, cur + 1, tar);
    }
    ListNode* getTreeLevel(TreeNode* root, int dep) {
        // write code here
        ListNode head(0);
        ListNode* tail = &head;
        getLevelNodes(root, &tail, 1, dep);
        return head.next;
    }
};
