/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* MeetingNode(ListNode *head)
    {
        if(!head)
            return NULL;
        ListNode *fast, *slow;
        slow = head->next;
        if(!slow)
            return NULL;
        fast = slow->next;
        while(fast && slow)
        {
            if(fast == slow)
                return fast;
            slow = slow->next;
            fast = fast->next;
            if(fast)
               fast = fast->next; 
        }
        return NULL;
    }
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
		ListNode* meeting = MeetingNode(pHead);
        if(meeting == NULL)
            return NULL;
        int n = 1;
        ListNode* walker1 = meeting;
        while(walker1->next != meeting)
        {
            walker1 = walker1->next;
            n++;
        }
        ListNode* walker2;
        walker1 = walker2 = pHead;
        for(int i = 0; i < n; i++)
            walker1 = walker1->next;
        while(walker1 != walker2)
        {
            walker1 = walker1->next;
            walker2 = walker2->next;
        }
        return walker1;
    }
};
