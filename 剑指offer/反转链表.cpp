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
    ListNode* ReverseList(ListNode* pHead) {
		if(!pHead)
            return NULL;
        ListNode *next, *new_head, *tmp;
        new_head = pHead;
        next = pHead->next;
        pHead->next = NULL;
        while(next)
        {
            tmp = next;
            next = next->next;
            tmp->next = new_head;
            new_head = tmp;
        }
        return new_head;
    }
};
