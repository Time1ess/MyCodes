/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Partition {
public:
    ListNode* partition(ListNode* pHead, int x) {
        // write code here
        ListNode lessHead(0), largerHead(0);
        ListNode *small, *larger;
        small = &lessHead;
        larger = &largerHead;
        while(pHead) {
            ListNode* next = pHead->next;
            pHead->next = NULL;
            if(pHead->val < x) {
                small->next = pHead;
                small = small->next;
            } else {
                larger->next = pHead;
                larger = larger->next;
            }
            pHead = next;
        }
        small->next = largerHead.next;
        return lessHead.next;
    }
};
