/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* merge(ListNode* l1, ListNode* l2)
    {
        if(!l1 || !l2)
            return l1 ? l1 : l2;
        ListNode head(0);
        ListNode* t = &head;
        while(l1 && l2)
        {
            if(l1->val < l2->val)
            {
                t->next = l1;
                l1 = l1->next;
            }
            else
            {
                t->next = l2;
                l2 = l2->next;
            }
            t = t->next;
            t->next = NULL;
        }
        if(l1)
            t->next = l1;
        else if(l2)
            t->next = l2;
        return head.next;
    }
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *l1 = head;
        ListNode *l2 = slow->next;
        slow->next = NULL;
        l1 = sortList(l1);
        l2 = sortList(l2);
        return merge(l1, l2);
    }
};
