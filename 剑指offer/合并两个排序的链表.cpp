/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(!pHead1 || !pHead2)
            return pHead1 ? pHead1 : pHead2;
        ListNode *new_head, *new_tail, *tmp;
        new_head = pHead1->val <= pHead2->val ? pHead1 : pHead2;
        new_tail = new_head;
        if(new_head == pHead1)
            pHead1 = pHead1->next;
        else
            pHead2 = pHead2->next;
        while(pHead1 && pHead2)
        {
           	if(pHead1->val <= pHead2->val)
            {
                tmp = pHead1->next;
                pHead1->next = NULL;
                new_tail->next = pHead1;
                pHead1 = tmp;
                new_tail = new_tail->next;
            }
            else
            {
                tmp = pHead2->next;
                pHead2->next = NULL;
                new_tail->next = pHead2;
                pHead2 = tmp;
                new_tail = new_tail->next;
            }
        }
        if(pHead1)
            new_tail->next = pHead1;
        else
            new_tail->next = pHead2;
        return new_head;
    }
};
