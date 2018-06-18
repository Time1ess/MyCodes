/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Plus {
public:
    ListNode* plusAB(ListNode* a, ListNode* b, int carry) {
        if(a == NULL && b == NULL) {
            if(carry == 0)
                return NULL;
            return new ListNode(carry);
        }
        ListNode* node = new ListNode(0);
        node->val = carry + (a != NULL ? a->val : 0) + (b != NULL ? b->val : 0);
        if(node->val >= 10) {
            node->val %= 10;
            node->next = plusAB(a ? a->next : NULL, b ? b->next : NULL, 1);
        } else {
            node->next = plusAB(a ? a->next : NULL, b ? b->next : NULL, 0);
        }
        return node;
    }
    ListNode* plusAB(ListNode* a, ListNode* b) {
        return plusAB(a, b, 0);
    }
};
