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
        ListNode* new_head = NULL;
        
        if(pHead1->val <= pHead2->val)
        {
            new_head = pHead1;
            new_head->next = Merge(pHead1->next, pHead2);
        }
        else
        {
            new_head = pHead2;
            new_head->next = Merge(pHead1, pHead2->next);
        }
        return new_head;
    }
};
