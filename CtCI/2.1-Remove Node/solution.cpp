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
        if(removeNode(pNode->next) == false) {
            delete pNode->next;
            pNode->next = NULL;
        }
        return true;
    }
};
