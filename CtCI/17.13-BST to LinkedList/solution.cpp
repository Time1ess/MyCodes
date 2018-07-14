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
class Converter {
public:
    void in_order(TreeNode* root, ListNode** last) {
        if(!root)
            return;
        in_order(root->left, last);
        ListNode *node = new ListNode(root->val);
        (*last)->next = node;
        *last = node;
        in_order(root->right, last);
    }
    ListNode* treeToList(TreeNode* root) {
        // write code here
        ListNode head(0);
        ListNode* last = &head;
        in_order(root, &last);
        return head.next;
    }
};
