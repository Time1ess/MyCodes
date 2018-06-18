/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Remove {
public:
    bool removeNode(ListNode* pNode) {
        // write code here
        if(pNode->next == NULL)
            return false;
        pNode->val = pNode->next->val;
        ListNode* tmp = pNode->next;
        pNode->next = tmp->next;
        delete tmp;
        return true;
    }
};
